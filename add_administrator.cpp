#include "add_administrator.h"
#include "ui_add_administrator.h"

Add_administrator::Add_administrator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_administrator)
{
    ui->setupUi(this);
}

Add_administrator::~Add_administrator()
{
    delete ui;
}
