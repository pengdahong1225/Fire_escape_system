#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"help_router.h"
#include"udpthread.h"
#include"add_fireman.h"

#include <QMainWindow>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QSqlDatabase>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void send_GET_Request();
public slots:
    void Open_Video();
    void getback(QNetworkReply *reply);
    void Open_help_router();
    void finishedThreadBtnSlot();
    void recevie_ok(QImage image);
    void set_stack(int page);
    void shoot_take_pic();
    void select_Fire_Fic();
    void Func_Add_fireman();
    void select_Escape_map();

    void slots_catchCap();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *m_pHttpMgr;
    help_router *obj_help_router;
    UdpThread *obj_udpthread;
    Add_fireman *obj_add_fireman;
    QImage _image;
};

#endif // MAINWINDOW_H
