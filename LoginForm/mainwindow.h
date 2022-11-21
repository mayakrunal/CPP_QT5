#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>

#include <QMainWindow>
#include <QMessageBox>
#include <QString>

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QtCharts>
#include <QChartView>

#include <QBarSet>
#include <QBarSeries>

#include <QPieSeries>
#include <QPieSlice>

#include <QLineSeries>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   protected:
    // resize event
    void resizeEvent(QResizeEvent *event);

   private slots:
    void btnSubmitClicked();
    void stackWidgetCurrentPageChanged(int index);

   private:
    Ui::MainWindow *ui;

    // charts
    QChartView *chartViewBar;
    QChartView *chartViewPie;
    QChartView *chartViewLine;

    QSqlDatabase db;

    const QString dbDriverType = "QMYSQL";

    // methods
    void connectdb();
    void setUpEvents();
    void createBarChart();
    void createPieChart();
    void createLineChart();
};
#endif  // MAINWINDOW_H
