#include "mainwindow.h"
#include "fileThread.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
    setupSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    loadMenu = new QMenu(tr("&Load"), this);
    displayMenu = new QMenu(tr("&Display"), this);

    openAction = new QAction(tr("&Open Folder"), this);
    loadMenu->addAction(openAction);

    displaySTDemandAction = new QAction(tr("&Spatio-temporal demand"), this);
    displayTravelTimeAction = new QAction(tr("&Travel time"), this);
    displayOrderFeesAction = new QAction(tr("&Fee"), this);

    displayMenu->addAction(displaySTDemandAction);
    displayMenu->addAction(displayTravelTimeAction);
    displayMenu->addAction(displayOrderFeesAction);

    openAction->setCheckable(false);
    //openAction->setChecked(false);

    menuBar()->addMenu(loadMenu);
    menuBar()->addMenu(displayMenu);
}

void MainWindow::setupSignalSlots()
{
    connect(openAction, &QAction::triggered, this, &MainWindow::loadFile);
    connect(ui->loadDataButton, &QPushButton::clicked, this, &MainWindow::loadFile);

    connect(displaySTDemandAction, &QAction::triggered, this, &MainWindow::displaySTDemand);
    connect(ui->STDemandButton, &QPushButton::clicked, this, &MainWindow::displaySTDemand);
    connect(displayTravelTimeAction, &QAction::triggered, this, &MainWindow::displayTravelTime);
    connect(ui->travelTimeButton, &QPushButton::clicked, this, &MainWindow::displayTravelTime);
    connect(displayOrderFeesAction, &QAction::triggered, this, &MainWindow::displayOrderFees);
    connect(ui->orderFeesButton, &QPushButton::clicked, this, &MainWindow::displayOrderFees);

    connect(ui->allGridRadioButton, &QRadioButton::clicked, this, &MainWindow::allGridsSelected);
    connect(ui->oneGridRadioButton, &QRadioButton::clicked, this, &MainWindow::oneGridSelected);
}

void MainWindow::loadFile()
{
    FileThread* fileThread = new FileThread(&mainData, &gridData, ui->UIprogressBar);
    connect(fileThread, &FileThread::resultReady, this, &MainWindow::handleFileResults);
    connect(fileThread, &FileThread::finished, fileThread, &QObject::deleteLater);
    connect(fileThread, &FileThread::fileNumChanged, this, &MainWindow::setProgressBar);

    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "../",
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //qDebug() <<dirName;

    if (dirName.isEmpty()) {
        return;
    }

    QDir dir(dirName);
    QStringList nameFilters;
    nameFilters << "*.csv";
    QStringList fileList = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    //qDebug() <<fileList;
    fileThread->fileList = fileList;
    fileThread->directory = dir;

    allFileNum = fileList.count();
    ui->UIprogressBar->setMinimum(0);
    ui->UIprogressBar->setMaximum(allFileNum);

    fileThread->start();

    //    ProgressBarThread* progressBarThread = new ProgressBarThread(ui->UIprogressBar);
    //    connect(progressBarThread, &ProgressBarThread::resultReady, this, &MainWindow::handlePBResults);
    //    connect(progressBarThread, &ProgressBarThread::finished, progressBarThread, &QObject::deleteLater);

    //    progressBarThread->start();
}

void MainWindow::handleFileResults()
{
    qDebug() << "Load successfully.";
    fileLoaded = true;
}

void MainWindow::setProgressBar(quint16 fileNum)
{
    ui->UIprogressBar->setValue(fileNum);
}

void MainWindow::allGridsSelected()
{
    allGrids = true;
}

void MainWindow::oneGridSelected()
{
    oneGrids = true;
}


void MainWindow::displaySTDemand()
{
    if (!fileLoaded) {
        QMessageBox::warning(this, "Warning!", "Please load file fist!");
        return;
    }

    quint32 startTimeStamp = ui->startTimeEdit->dateTime().toSecsSinceEpoch();
    quint32 endTimeStamp = ui->endTimeEdit->dateTime().toSecsSinceEpoch();
    quint16 startDay = ui->startTimeEdit->date().day() - 1;
    quint16 endDay = ui->endTimeEdit->date().day() - 1;

    qDebug() << startTimeStamp << endTimeStamp << startDay << endDay;

    quint32 timeStep = 0;
    switch (ui->timeStepComboBox->currentIndex()) {
        case 0:
            timeStep = oneMinute;
            break;
        case 1:
            timeStep = 10 * oneMinute;
            break;
        case 2:
            timeStep = 30 * oneMinute;
            break;
        case 3:
            timeStep = oneHour;
            break;
        case 4:
            timeStep = 12 * oneHour;
            break;
        case 5:
            timeStep = oneDay;
    }

    qDebug() << allGrids << oneGrids;

    QChart* chart = new QChart();
    if (allGrids) {
        //All grids in Chengdu are selected.
        chart->setTitle("The number of orders in Chengdu over time");
        QLineSeries* orderNumSeries = new QLineSeries();

        quint32 startIndex = 0;
        for (qint32 i = 0; i < mainData[startDay].size(); ++i) {
            if (mainData[startDay][i].departure_time == startTimeStamp) {
                startIndex = i;
                break;
            }
        }

        //TODO: debug
        quint32 orderCount = 0;
        quint32 curTimeStamp = startTimeStamp;
        quint16 curDay = startDay;
        for (qint32 i = startIndex; mainData[curDay][i].departure_time <= endTimeStamp; ++i) {
            //qDebug() <<i;
            if (mainData[curDay][i].mid_time < curTimeStamp + timeStep) {
                ++orderCount;
            } else {
                qDebug() << orderCount;
                orderNumSeries->append(curTimeStamp, orderCount);
                curTimeStamp += timeStep;
                orderCount = 0;
            }

            if (i == mainData[curDay].size() - 1) {
                ++curDay;
                i = -1;
            }
        }

        chart->addSeries(orderNumSeries);

        chart->createDefaultAxes();

        ui->graphicsView->setChart(chart);

    } else if (oneGrids) {
        //Only one grid is selected.


    } else {
        qDebug() << "Please select grid area.";
    }
}

void MainWindow::displayTravelTime()
{
    if (!fileLoaded) {
        QMessageBox::warning(this, "Warning!", "Please load file fist!");
        return;
    }
}

void MainWindow::displayOrderFees()
{
    if (!fileLoaded) {
        QMessageBox::warning(this, "Warning!", "Please load file fist!");
        return;
    }
}
