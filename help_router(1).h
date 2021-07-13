#ifndef HELP_ROUTER_H
#define HELP_ROUTER_H

#include <QDialog>
#include<QAxWidget>

namespace Ui {
class help_router;
}

class help_router : public QDialog
{
    Q_OBJECT
public:
    explicit help_router(QWidget *parent = nullptr);
    ~help_router();

private:
    Ui::help_router *ui;
    QAxWidget *axwidget;
};

#endif // HELP_ROUTER_H
