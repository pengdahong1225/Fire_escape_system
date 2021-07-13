#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QAction>
#include<QToolBar>
#include<QList>
#include<QStatusBar>
#include<QMessageBox>
#include<QNetworkRequest>
#include<QNetworkReply>
#include<QDebug>
#include<QFile>
#include<QFileInfo>
#include<QUdpSocket>
#include<QLineEdit>
#include<QPushButton>
#include<QLabel>
#include<QTimer>
#include<chrono>
#include<thread>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("消防逃生系统"));

    QAction *shoot_action = ui->menu->addAction("抓拍");
    shoot_action->setStatusTip(tr("监控视频抓拍"));
    ui->menu->addSeparator();
    QAction *add_Firemen = ui->menu->addAction("录入管理员");
    add_Firemen->setStatusTip(tr("添加管理员信息"));

    QAction *select_Escape_route = ui->menu1->addAction("查询逃生路线");
    select_Escape_route->setStatusTip(tr("查询逃生路线"));
    ui->menu1->addSeparator();
    QAction *select_help_route = ui->menu1->addAction("查询救援路线");
    select_help_route->setStatusTip(tr("查询消防救援路线"));
    ui->menu1->addSeparator();
    QAction *select_FireFacility = ui->menu1->addAction("查询消防设施");
    select_FireFacility->setStatusTip(tr("查询楼道消防设施的位置情况"));

    QAction *select_windowdata = ui->menu_2->addAction("报警器位置");
    select_windowdata->setStatusTip(tr("查询烟雾报警器位置"));
    ui->menu1->addSeparator();
    QAction *Video = ui->menu_2->addAction("监控视频");
    Video->setStatusTip(tr("查看监控录像"));
    ui->menu_2->addSeparator();

    QToolBar *toolbar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea,toolbar);
    toolbar->setAllowedAreas(Qt::TopToolBarArea);
    toolbar->setMovable(false);
    toolbar->addAction(shoot_action);
    toolbar->addSeparator();
    toolbar->addAction(add_Firemen);
    toolbar->addSeparator();
    toolbar->addAction(select_windowdata);
    toolbar->addSeparator();
    toolbar->addAction(select_Escape_route);
    toolbar->addSeparator();
    toolbar->addAction(select_help_route);
    toolbar->addSeparator();
    toolbar->addAction(select_FireFacility);
    toolbar->addSeparator();
    toolbar->addAction(Video);
    toolbar->addSeparator();
    statusBar();

    _image = QImage();

    connect(Video,&QAction::triggered,this,&MainWindow::Open_Video);
    connect(select_help_route,&QAction::triggered,this,&MainWindow::Open_help_router);

    m_pHttpMgr = new QNetworkAccessManager(this);
    connect(this->m_pHttpMgr,&QNetworkAccessManager::finished,this,&MainWindow::getback);

    void (QComboBox::*psetpage)(int page) = &QComboBox::currentIndexChanged;//函数指针指定
    connect(ui->comboBox,psetpage,this,&MainWindow::set_stack);
    ui->stackedWidget->setCurrentIndex(0);
    connect(shoot_action,&QAction::triggered,this,&MainWindow::shoot_take_pic);

    connect(select_FireFacility,&QAction::triggered,this,&MainWindow::select_Fire_Fic);
    connect(add_Firemen,&QAction::triggered,this,&MainWindow::Func_Add_fireman);
    connect(select_Escape_route,&QAction::triggered,this,&MainWindow::select_Escape_map);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::send_GET_Request()
{
    //设置url
    QString Url = "http://api.map.baidu.com/direction?origin=latlng:103.60298,30.894435&destination=latlng:103.662427,31.014353&mode=driving&output=html&coord_type=bd09ll&src=webapp.baidu.openAPIdemo";
    QNetworkRequest requestInfo;
    requestInfo.setUrl(QUrl(Url));
    this->m_pHttpMgr->get(requestInfo);
}

void MainWindow::Open_Video()
{
    this->obj_udpthread = new UdpThread(this);
    connect(this->obj_udpthread,&UdpThread::finished,this,
            &MainWindow::finishedThreadBtnSlot);
    connect(this->obj_udpthread,&UdpThread::recevie_success,this,&MainWindow::recevie_ok);
    obj_udpthread->start();
    /*cv::VideoCapture capture(0);
    cv::Mat frame;
    while(true)
    {
        capture >> frame;
        cv::imshow("读取视频",frame);
        cv::waitKey(30);
    }*/
}

void MainWindow::finishedThreadBtnSlot()
{
    qDebug()<<"udp线程执行结束";
    this->obj_udpthread->quit();
}

void MainWindow::recevie_ok(QImage image)
{
    if(image.isNull())
    {
        qDebug()<<"Image is Null";
        return;
    }
    qDebug()<<"Image is not Null";
    ui->label_7->setScaledContents(true);
    ui->label_7->setPixmap(QPixmap::fromImage(image));
    _image = image;
}

void MainWindow::set_stack(int page)
{
    ui->stackedWidget->setCurrentIndex(page);
}

void MainWindow::shoot_take_pic()
{
    if(_image.isNull())
        QMessageBox::information(this,tr("火灾逃生"),tr("摄像头没有打开"),QMessageBox::Ok);
    else {
        QDialog *dia_wid = new QDialog(this);
        dia_wid->resize(280,250);

        dia_wid->setWindowTitle(tr("抓拍"));
        QLabel *one_img = new QLabel(dia_wid);
        one_img->setScaledContents(true);
        one_img->setPixmap(QPixmap::fromImage(_image));
        dia_wid->show();
        dia_wid->setAttribute(Qt::WA_DeleteOnClose);
    }
}

void MainWindow::select_Fire_Fic()
{
    int i = ui->stackedWidget->currentIndex();
    if(i ==0)
        return;
    QString path = QString("../pic/%1.jpg").arg(i);
    QPixmap *photo = new QPixmap;
    photo->load(path);
    if(i == 1)
    {
        ui->label_10->setScaledContents(true);
        ui->label_10->setPixmap(*photo);
    }
    else if(i ==2)
    {
        ui->label_16->setScaledContents(true);
        ui->label_16->setPixmap(*photo);
    }
    else if(i ==3)
    {
        ui->label_22->setScaledContents(true);
        ui->label_22->setPixmap(*photo);
    }
}

void MainWindow::Func_Add_fireman()
{
    obj_add_fireman = new Add_fireman(this);
    obj_add_fireman->setAttribute(Qt::WA_DeleteOnClose);
    obj_add_fireman->show();
}

void MainWindow::select_Escape_map()
{
    QPixmap *escape_map = new QPixmap;
    escape_map->load("../pic/逃生图1.jpg");
    ui->label_8->setPixmap(*escape_map);
    ui->label_8->setScaledContents(true);
    ui->label_14->setPixmap(*escape_map);
    ui->label_14->setScaledContents(true);
    ui->label_24->setPixmap(*escape_map);
    ui->label_24->setScaledContents(true);
}

void MainWindow::getback(QNetworkReply *reply) //请求数据
{
    QByteArray array = reply->readAll();
    qDebug()<<array.data();

    QFileInfo filepath("../map.json");
    if(filepath.isFile())
    {
        //存在
    }
    else {
        //不存在,创建一个json文件
        QFile *file = new QFile("../map.json");
        file->open(QIODevice::WriteOnly);
        file->close();
    }
    //把replay写到json中
    QFile _map_file("../map.json");
    if(_map_file.open(QIODevice::WriteOnly))
    {
        _map_file.write(array);
    }
    else {
        qDebug()<<"map_json文件存在,但打开失败";
    }
}
void MainWindow::Open_help_router()
{
    //get请求
    //this->send_GET_Request();
    obj_help_router = new help_router(this);
    obj_help_router->show();
}
