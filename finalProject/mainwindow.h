#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTextBrowser>
#include <QList>


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

    QList<QList<QList<double>>> mainData;

    QList<QList<double>> gridData;

};
#endif // MAINWINDOW_H
