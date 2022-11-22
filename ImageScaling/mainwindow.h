#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
    void paintImage(QString fileName,int x,int y);

private slots:
    void btnBrowseClicked();
    void btnSaveClicked();
    void scaleSliderValueChanged(int value);
    void leftSliderValueChanged(int value);
    void topSliderValueChanged(int value);


private:
    Ui::MainWindow *ui;
    bool canDraw;
    QPixmap *pix;
    QSize imageSize;
    QSize drawSize;
    QPoint drawPos;

    void setupEvents();
};
#endif // MAINWINDOW_H
