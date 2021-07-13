#include "fun_sql.h"
bool connnect_sql(QSqlDatabase &db)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("1225");
    db.setDatabaseName("login");
    if(db.open())
        return true;
    else
        return false;
}
