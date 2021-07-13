#include "main_login.h"
#include "ui_main_login.h"
#include"fun_sql.h"
#include<QMessageBox>
#include<QSqlQuery>

main_login::main_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_login)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("消防逃生系统"));
    //图片插入
    QPixmap pixmap_1(":/prefix1/pic/yonghu.png");
    ui->label_login->setPixmap(pixmap_1);
    QPixmap pixmap_2(":/prefix1/pic/mima.png");
    ui->label_passwd->setPixmap(pixmap_2);
    QPixmap pixmap_3(":/prefix1/pic/huozai.png");
    ui->label_pic1->setPixmap(pixmap_3);
    QPixmap pixmap_4(":/prefix1/pic/huo.png");
    ui->label_pic2->setPixmap(pixmap_4);
    //背景
    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(255,228,188)));

    ui->lineEdit_login->setStyleSheet("QLineEdit{border-width:1px;border-radius:4px;color:black;border:1px solid gray;}");
    ui->lineEdit_login->setClearButtonEnabled(true);
    ui->lineEdit_passwd->setStyleSheet("QLineEdit{border-width:1px;border-radius:4px;color:black;border:1px solid gray;}");
    ui->lineEdit_passwd->setClearButtonEnabled(true);
    ui->pushButton_login->setStyleSheet("QPushButton{"
                                        "background-color:rgba(100,225,100,30);"
                                        "border-style:outset;"
                                        "border-width:4px;"
                                        "border-radius:10px;"
                                        "border-color:rgba(255,255,255,30);"
                                        "color:rgba(0,0,0,100);"
                                        "padding:6px;"
                                        "}"
                                        //鼠标按下样式
                                        "QPushButton:pressed{"
                                        "background-color:rgba(100,255,100,200);"
                                        "border-color:rgba(255,255,255,30);"
                                        "border-style:inset;"
                                        "color:rgba(0,0,0,100);"
                                        "}"
                                        //鼠标悬停样式
                                        "QPushButton:hover{"
                                        "background-color:rgba(100,255,100,100);"
                                        "border-color:rgba(255,255,255,200);"
                                        "color:rgba(0,0,0,200);"
                                        "}");
    connect(ui->pushButton_login,&QPushButton::clicked,this,&main_login::connect_login);
    connect(ui->lineEdit_passwd,&QLineEdit::returnPressed,ui->pushButton_login,&QPushButton::click,Qt::UniqueConnection);
}

main_login::~main_login()
{
    delete ui;
}

void main_login::connect_login()
{
    if(ui->lineEdit_login->text().isEmpty())
    {
        QMessageBox::critical(this,"warning","name不能为空",QMessageBox::Yes);
    }
    else if(ui->lineEdit_passwd->text().isEmpty())
    {
        QMessageBox::critical(this,"warning","passwd不能为空",QMessageBox::Yes);
    }
    else
    {
        QString name = ui->lineEdit_login->text();
        QString passwd = ui->lineEdit_passwd->text();
        qDebug()<<name<<passwd;
        this->main_window = new MainWindow;
        //与数据库进行对比
        bool is_ok = false;
        QSqlDatabase db;
//        if(connnect_sql(db))
//        {
//            qDebug()<<"connect to mysql is success";
//            QSqlQuery query(db);
//            query.exec("select * from fireman");
//            while(query.next())
//            {
//                QString _getname = query.value(0).toString();
//                QString _getphone_number = query.value(1).toString();
//                if(name == _getname && passwd == _getphone_number)
//                    is_ok = true;
//            }
//            if(is_ok == false)
//            {
//                QMessageBox::warning(this,"warning","验证失败",QMessageBox::Close);
//                db.close();
//            }
//            else {
                main_window->show();
                db.close();
                this->showMinimized();
//            }
//        }
//        else {
//            qDebug()<<"connect to mysql is error";
//            QMessageBox::warning(this,"warning","请检查网络",QMessageBox::Ok);
//        }
    }
}
