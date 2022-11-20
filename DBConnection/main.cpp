#include "qdebug.h"
#include "qsqldatabase.h"
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>


void showDepartments(QSqlDatabase db){
    QString command = "SELECT name FROM department";
    QSqlQuery query(db);
    if(query.exec(command)){
        while(query.next()){
            QString name = query.value("name").toString();
            qDebug() << name;
        }
    }
}
void showDepartmentUsers(QSqlDatabase db){
    QString command = "SELECT a.username,b.name FROM user as a inner join department as b on a.deptId = b.id where a.status = 0";
    QSqlQuery query(db);
    if(query.exec(command)){
        while(query.next()){
            QString username = query.value("username").toString();
            QString deptname = query.value("name").toString();
            qDebug() << username <<deptname;
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("QtPocDb");
    db.setUserName("mysql");
    db.setPassword("mysql@123");
    if(db.open()){
        qDebug() << "Connected!";
        showDepartments(db);
        showDepartmentUsers(db);

    }else{
        qDebug() << "Failed to Connect!";
    }
    return a.exec();
}
