#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dataForm.h"
#include "global.h"
#include <QDebug>
#include <QMainWindow>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void loadFile();
    //void display();
    void handleFileResults(QString);
    void setProgressBar(quint16);

    void displaySTDemand();//display the spatio-temporal demand patterns.
    void displayTravelTime();
    void displayOrderFees();

    void orderIDChanged(quint32);
    void depTimechanged(quint32);
    void endTimeChanged(quint32);
    void origChanged(quint32);
    void destChanged(quint32);
    void feeChanged(quint32);


    void allGridsSelected();
    void oneGridSelected();

    void handleSTCountResults(QString);
    void handleTimeCountResults(QString);
    void handleFeesCountResults(QString);
    //void reloadChart();

private:
    Ui::MainWindow* ui;
    void setupUI();
    void setupSignalSlots();
    void Lagrange_interpolation(QVector<qint64>&, QVector<qint64>&, quint32);

    QMenu* loadMenu;
    QMenu* displayMenu;

    QAction* openAction;
    QAction* displaySTDemandAction;
    QAction* displayTravelTimeAction;
    QAction* displayOrderFeesAction;

    QChart* chart;
    QDateTimeAxis* axisX = new QDateTimeAxis;
    QValueAxis* axisY = new QValueAxis;

    QVector<QVector<orderDataForm>> mainData;
    QVector<QVector<coordinate>> gridData;

    quint32 allFileNum = 0;//allFileNum只会在main thread用到，所以定义为数据成员

    bool fileLoaded = 0;


};
#endif// MAINWINDOW_H
