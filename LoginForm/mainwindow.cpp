#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Events
    connect(ui->btnSubmit,&QPushButton::clicked,this,&MainWindow::btnSubmitClicked);

    //database connect
    connectdb();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectdb(){
    db = QSqlDatabase::addDatabase(dbDriverType);
    db.setHostName("localhost");
    db.setUserName("mysql");
    db.setPassword("mysql@123");
    db.setDatabaseName("QtPocDb");
    if(db.open()){
        qDebug() << "Connected!";
    }else{
        qDebug() << "Failed to connect.";
    }
}

void MainWindow::btnSubmitClicked(){
        qDebug() << "Button Clicked!";
        QString username = ui->lineEditUserName->text();
        QString password = ui->lineEditPassword->text();
        qDebug() << username << password;

        QString command = "SELECT * FROM user WHERE username = '" + username + "' AND Password = '" + password+ "' AND status = 0";
        QSqlQuery query(db);
        if(query.exec(command)){
            if(query.size() > 0){
                QMessageBox::information(this,"Login Success","You have successfully logged in!");
            }else{
                QMessageBox::information(this,"Login Failed","Login failed. Please try again.");
            }
        }
}
