#ifndef MAIN_LOGIN_H
#define MAIN_LOGIN_H

#include <QWidget>
#include"mainwindow.h"

namespace Ui {
class main_login;
}

class main_login : public QWidget
{
    Q_OBJECT

public:
    explicit main_login(QWidget *parent = nullptr);
    ~main_login();
public slots:
    void connect_login();
private:
    Ui::main_login *ui;
    MainWindow *main_window;
};

#endif // MAIN_LOGIN_H
