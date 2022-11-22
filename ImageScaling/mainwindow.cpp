#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setup the events
    setupEvents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupEvents(){
    connect(ui->btnBrowse,&QPushButton::clicked,this,&MainWindow::btnBrowseClicked);
    connect(ui->btnSave,&QPushButton::clicked,this,&MainWindow::btnSaveClicked);
    connect(ui->scaleSlider,&QSlider::valueChanged,this,&MainWindow::scaleSliderValueChanged);
    connect(ui->leftSlider,&QSlider::valueChanged,this,&MainWindow::leftSliderValueChanged);
    connect(ui->topSlider,&QSlider::valueChanged,this,&MainWindow::topSliderValueChanged);
}


void MainWindow::btnBrowseClicked(){
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),QDir::currentPath(),tr("Image Files (*.jpg *.jpeg)"));

    if(!fileName.isEmpty()){
        QPixmap *newPix = new QPixmap(fileName);
        if(!newPix->isNull()){
            if(newPix->width() < 150 || newPix->height() < 150){
                QMessageBox::warning(this,tr("Invalid Size"),tr("Image size too small. Please use an image larger than 150x105."));
                return;
            }
            pix = newPix;
            imageSize = pix->size();
            drawSize = pix->size();
            canDraw = true;
        }else{
            canDraw = false;
            QMessageBox::warning(this,tr("Invalid Image"),tr("Invalid or corrupted file. Please try again with another image."));
        }
    }
}

void MainWindow::btnSaveClicked(){
    if(canDraw){
      if(!pix->isNull()){
            //save the new pic from painter
          paintImage(QCoreApplication::applicationDirPath() + "/image.jpg",0,0);
      }
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    if(canDraw){
        paintImage("",ui->productImage->pos().x(),ui->productImage->pos().y());
    }
}

void MainWindow::paintImage(QString fileName, int x, int y){
    QPainter painter;
    QImage saveImage(150,150,QImage::Format_RGB16);

    if(!fileName.isEmpty()){
        painter.begin(&saveImage);
    }else{
        painter.begin(this);
    }

    if(!pix->isNull()){
        painter.setClipRect(x,y,150,150);
        painter.fillRect(QRect(x,y,150,150),Qt::SolidPattern);
        painter.drawPixmap(x - drawPos.x(),y - drawPos.y(),drawSize.width(),drawSize.height(),*pix);
    }
    painter.end();

    if(fileName != ""){
        saveImage.save(fileName);
        QMessageBox::information(this,"Success","Image has been successfully saved!");
    }
}

void MainWindow::scaleSliderValueChanged(int value){
    drawSize = imageSize * value / 100;
    update();

}
void MainWindow::leftSliderValueChanged(int value){
    drawPos.setX(value * drawSize.width() / 100 * 0.5);
    update();
}
void MainWindow::topSliderValueChanged(int value){
    drawPos.setY(value * drawSize.height() / 100 * 0.5);
    update();
}
