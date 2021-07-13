#include "help_router.h"
#include "ui_help_router.h"

#include<QAxWidget>

help_router::help_router(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help_router)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("消防逃生系统"));

    this->axwidget = new QAxWidget(this);
    axwidget -> setGeometry(0,0,1114,704);
    axwidget -> setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));
    axwidget -> setFocusPolicy(Qt::StrongFocus);
    axwidget -> setProperty("DisplayAlerts",false);
    axwidget -> setProperty("DisplayScrollBars",true);

    axwidget -> dynamicCall("Navigate(const QString&)","http://api.map.baidu.com/direction?origin=latlng:103.60298,30.894435&destination=latlng:103.662427,31.014353&mode=driving&output=html&coord_type=bd09ll&src=webapp.baidu.openAPIdemo");
}

help_router::~help_router()
{
    delete ui;
}
