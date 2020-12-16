#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "dataForm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadFile();
    //void display();
    void handleFileResults(){
        qDebug()<<"Load successfully.";
    }
    void handlePBResults(){

    }



private:
    Ui::MainWindow *ui;
    void setupUI();
    void setupSignalSlots();

    QMenu* loadMenu;
    QMenu* displayMenu;

    QAction* openAction;
    QAction* displaySTAction;
    QAction* displayTravelTimeAction;
    QAction* displayFeeAction;

    QVector<QVector<orderDataForm>> mainData;
    QVector<gridDataForm> gridData;

};
#endif // MAINWINDOW_H
