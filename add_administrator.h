#ifndef ADD_ADMINISTRATOR_H
#define ADD_ADMINISTRATOR_H

#include <QDialog>

namespace Ui {
class Add_administrator;
}

class Add_administrator : public QDialog
{
    Q_OBJECT

public:
    explicit Add_administrator(QWidget *parent = nullptr);
    ~Add_administrator();

private:
    Ui::Add_administrator *ui;
};

#endif // ADD_ADMINISTRATOR_H
