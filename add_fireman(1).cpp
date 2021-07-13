#include "add_fireman.h"
#include "ui_add_fireman.h"
#include"fun_sql.h"
#include<QDebug>
#include<QSqlQuery>
#include<QMessageBox>

Add_fireman::Add_fireman(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_fireman)
{
    ui->setupUi(this);
    this->setWindowTitle("Add administrator");
    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(255,228,188)));
    ui->lineEdit->setStyleSheet("\nborder: 1px solid gray;/*设置边框的粗细，以及颜色*/\nborder-radius: 10px;/*设置圆角的大小*/\npadding: 0 8px;/*如果没有内容光标在开始往后移动0.8像素点*/\nselection-background-color: darkgray;");
    ui->lineEdit->setClearButtonEnabled(true);
    ui->lineEdit_2->setStyleSheet("\nborder: 1px solid gray;/*设置边框的粗细，以及颜色*/\nborder-radius: 10px;/*设置圆角的大小*/\npadding: 0 8px;/*如果没有内容光标在开始往后移动0.8像素点*/\nselection-background-color: darkgray;");
    ui->lineEdit_2->setClearButtonEnabled(true);
    connect(ui->pushButton,&QPushButton::clicked,this,&Add_fireman::Func_toAdd);
    connect(ui->lineEdit_2,&QLineEdit::returnPressed,ui->pushButton,&QPushButton::click,Qt::UniqueConnection);
}

Add_fireman::~Add_fireman()
{
    delete ui;
}

void Add_fireman::Func_toAdd()
{
    if(!ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty())
    {
        QString name = ui->lineEdit->text();
        QString phone_number = ui->lineEdit_2->text();
        qDebug()<<name<<phone_number;
        bool is_exist = false;
        QSqlDatabase db;
        if(connnect_sql(db))
        {
            qDebug()<<"connect to mysql is success";
            QSqlQuery query(db);
            query.exec("select * from fireman");//先查找存不存在
            while(query.next())
            {
                QString _getname = query.value(0).toString();
                if(name == _getname)
                    is_exist = true;
            }
            if(is_exist == false)  //不存在，添加
            {
                QString str = QString("insert into fireman(name,phone_number) values('%1','%2')").arg(name).arg(phone_number);
                qDebug()<<str;
                query.exec(str);
            }
            else {                  //存在，提示
                QMessageBox::information(this,"Add administrator","该成员已存在",QMessageBox::Cancel);
            }
        }
        else {
            qDebug()<<"connect to mysql is error";
            QMessageBox::warning(this,"warning","请检查网络",QMessageBox::Ok);
        }
    }
}
