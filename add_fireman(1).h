#ifndef ADD_FIREMAN_H
#define ADD_FIREMAN_H

#include <QDialog>

namespace Ui {
class Add_fireman;
}

class Add_fireman : public QDialog
{
    Q_OBJECT

public:
    explicit Add_fireman(QWidget *parent = nullptr);
    ~Add_fireman();
public slots:
    void Func_toAdd();

private:
    Ui::Add_fireman *ui;
};

#endif // ADD_FIREMAN_H
