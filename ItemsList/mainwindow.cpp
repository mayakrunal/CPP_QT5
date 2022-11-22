#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //List Widget
    ui->listWidget->addItem("Test Item");
    QListWidgetItem *listItem = new QListWidgetItem;
    listItem->setText("My Second Item");
    listItem->setData(100,1000);
    ui->listWidget->addItem(listItem);

    //tree widget items
    QTreeWidgetItem *treeItem = new QTreeWidgetItem;
    treeItem->setText(0,"My Test Item");
    ui->treeWidget->addTopLevelItem(treeItem);
    QTreeWidgetItem *treeItem2 = new QTreeWidgetItem;
    treeItem2->setText(0,"My Test Subitem");
    treeItem->addChild(treeItem2);

    QString file = QFileDialog::getOpenFileName(this);
    qDebug() << file;
}

MainWindow::~MainWindow()
{
    delete ui;
}

