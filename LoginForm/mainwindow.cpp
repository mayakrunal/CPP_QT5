#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // Setup Events
    setUpEvents();

    //Set default page to the Login Page
    ui->stackedWidget->setCurrentWidget(ui->loginPage);

    // database connect
    connectdb();

    //create the charts
    createBarChart();
    createPieChart();
    createLineChart();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpEvents(){
    connect(ui->btnSubmit, &QPushButton::clicked, this, &MainWindow::btnSubmitClicked);
    connect(ui->stackedWidget,&QStackedWidget::currentChanged,this,&MainWindow::stackWidgetCurrentPageChanged);
}

void MainWindow::connectdb() {
    db = QSqlDatabase::addDatabase(dbDriverType);
    db.setHostName("localhost");
    db.setUserName("mysql");
    db.setPassword("mysql@123");
    db.setDatabaseName("QtPocDb");
    if (db.open()) {
        qDebug() << "Connected!";
    } else {
        qDebug() << "Failed to connect.";
    }
}

void MainWindow::resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent(event);
    chartViewBar->resize(chartViewBar->parentWidget()->size());
    chartViewPie->resize(chartViewPie->parentWidget()->size());
    chartViewLine->resize(chartViewLine->parentWidget()->size());
}

void MainWindow::btnSubmitClicked() {
    qDebug() << "Button Clicked!";
    QString username = ui->lineEditUserName->text();
    QString password = ui->lineEditPassword->text();
    qDebug() << username << password;

    QString command = "SELECT * FROM user WHERE username = '" + username + "' AND Password = '" + password + "' AND status = 0";
    QSqlQuery query(db);
    if (query.exec(command)) {
        if (query.size() > 0) {
            QMessageBox::information(this, "Login Success", "You have successfully logged in!");
            ui->stackedWidget->setCurrentWidget(ui->dashBoardPage);
        } else {
            QMessageBox::information(this, "Login Failed", "Login failed. Please try again.");
        }
    }
}


void MainWindow::stackWidgetCurrentPageChanged(int index){
    qDebug() <<"Stack Widget Current Page Changed to " + QString::number(index) + " index";
    if(index == 1){

    }
}

void MainWindow::createBarChart(){
    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");
    QBarSet *set3 = new QBarSet("Mary");
    QBarSet *set4 = new QBarSet("Samantha");

    *set0 << 10 << 20 << 30 << 40 << 50 << 60;
    *set1 << 50 << 70 << 40 << 45 << 80 << 70;
    *set2 << 30 << 50 << 80 << 13 << 80 << 50;
    *set3 << 50 << 60 << 70 << 30 << 40 << 25;
    *set4 << 90 << 70 << 50 << 30 << 16 << 42;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    QChart *chartBar = new QChart();
    chartBar->addSeries(series);
    chartBar->setTitle("Student Performance");
    chartBar->setAnimationOptions(QChart::SeriesAnimations);

    QStringList catagories;
    catagories << "Jan" <<"Feb"<<"Mar"<<"Apr"<<"May"<<"Jun";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(catagories);
    chartBar->createDefaultAxes();
    chartBar->setAxisX(axis,series);

    chartViewBar = new QChartView(chartBar);
    chartViewBar->setParent(ui->chart1);
}


void MainWindow::createPieChart(){
    QPieSeries *series = new QPieSeries();
    series->append("Jane",10);
    series->append("Joe",20);
    series->append("Andy",30);
    series->append("Barbara",40);
    series->append("Jason",50);

    QPieSlice *slice = series->slices().at(1);
    slice->setExploded();
    slice->setLabelVisible();
    slice->setPen(QPen(Qt::darkGreen,2));
    slice->setBrush(Qt::green);

    QChart *chartPie = new QChart();
    chartPie->addSeries(series);
    chartPie->setTitle("Student Performance");
    chartPie->setAnimationOptions(QChart::AllAnimations);

    chartViewPie = new QChartView(chartPie);
    chartViewPie->setRenderHint(QPainter::Antialiasing);
    chartViewPie->setParent(ui->chart2);
}

void MainWindow::createLineChart(){
    QLineSeries *seriesLine = new QLineSeries();
    seriesLine->append(0,6);
    seriesLine->append(2,4);
    seriesLine->append(3,8);
    seriesLine->append(4,4);
    seriesLine->append(10,5);
    seriesLine->append(11,10);
    seriesLine->append(13,3);
    seriesLine->append(17,6);
    seriesLine->append(18,3);
    seriesLine->append(20,2);

    QChart *chartLine = new QChart();
    chartLine->addSeries(seriesLine);
    chartLine->createDefaultAxes();
    chartLine->setTitle("Student Performance");

    chartViewLine = new QChartView(chartLine);
    chartViewLine->setRenderHint(QPainter::Antialiasing);
    chartViewLine->setParent(ui->chart3);
}
