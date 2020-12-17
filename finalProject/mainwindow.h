#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dataForm.h"
#include "global.h"
#include <QDebug>
#include <QMainWindow>

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
    void handleFileResults();
    void setProgressBar(quint16);

    void displaySTDemand();//display the spatio-temporal demand patterns.
    void displayTravelTime();
    void displayOrderFees();

    void allGridsSelected();
    void oneGridSelected();

private:
    Ui::MainWindow* ui;
    void setupUI();
    void setupSignalSlots();

    QMenu* loadMenu;
    QMenu* displayMenu;

    QAction* openAction;
    QAction* displaySTDemandAction;
    QAction* displayTravelTimeAction;
    QAction* displayOrderFeesAction;

    QVector<QVector<orderDataForm>> mainData;
    QVector<gridDataForm> gridData;

    bool fileLoaded = 0;
    bool allGrids = 0;
    bool oneGrids = 0;

};
#endif// MAINWINDOW_H
