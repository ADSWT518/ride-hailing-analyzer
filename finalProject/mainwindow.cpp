#include "mainwindow.h"
#include "countThread.h"
#include "fileThread.h"
#include "global.h"
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

    chart = new QChart();

    ui->timeStepSpinBox->setMinimum(1);
    switch (ui->timeStepComboBox->currentIndex()) {
        case 0:
            ui->timeStepSpinBox->setMaximum(59);
            break;
        case 1:
            ui->timeStepSpinBox->setMaximum(23);
            break;
        case 2:
            ui->timeStepSpinBox->setMaximum(15);
    }
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

    //TODO: debug
    connect(ui->timeStepSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
        [=](int i){
        //timeStep = i * timeUnit[ui->timeStepComboBox->currentIndex()];
        displaySTDemand();
    });
    connect(ui->timeStepComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index){
        displaySTDemand();
    });
    connect(ui->timeStepComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index){
        ui->timeStepSpinBox->setMaximum(timeUnitMax[index]);
    });

}

void MainWindow::loadFile()
{
    FileThread* fileThread = new FileThread(&mainData, &gridData);
    connect(fileThread, &FileThread::resultReady, this, &MainWindow::handleFileResults);
    connect(fileThread, &FileThread::finished, fileThread, &QObject::deleteLater);
    connect(fileThread, &FileThread::fileNumChanged, this, &MainWindow::setProgressBar);

    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "../",
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toLatin1();
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

}

void MainWindow::handleFileResults(QString r)
{
    qDebug() << r;
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

void MainWindow::handleCountResults(QString r)
{
    chart->removeAllSeries();

    qDebug() <<"chart->series().size()"<<chart->series().size();

    if (allGrids) {
        //All grids in Chengdu are selected.
        chart->setTitle("The number of orders in Chengdu over time");
        QLineSeries* orderNumSeries = new QLineSeries();
        //orderNumSeries->clear();

        for (qint32 i = 0; i < orderCountVector.size();++i) {
            orderNumSeries->append(startTimeStamp + timeStep * i, orderCountVector[i]);
            //qDebug() <<'('<<startTimeStamp + timeStep * i<<','<< orderCountVector[i]<<')';
        }
        chart->addSeries(orderNumSeries);
        qDebug() <<"chart->series().size()"<<chart->series().size();

        chart->createDefaultAxes();

        ui->graphicsView->setChart(chart);

    } else if (oneGrids) {
        //Only one grid is selected.


    } else {
        qDebug() << "Please select grid area.";
    }

    qDebug() <<r;
}


void MainWindow::reloadChart()
{
}

void MainWindow::displaySTDemand()
{
    if (!fileLoaded) {
        QMessageBox::warning(this, "Warning!", "Please load file fist!");
        return;
    }

    CountThread* countThread = new CountThread(&mainData);
    connect(countThread, &CountThread::resultReady, this, &MainWindow::handleCountResults);
    connect(countThread, &CountThread::finished, countThread, &QObject::deleteLater);



    startTimeStamp = ui->startTimeEdit->dateTime().toSecsSinceEpoch();
    endTimeStamp = ui->endTimeEdit->dateTime().toSecsSinceEpoch();
    startDay = ui->startTimeEdit->date().day() - 1;
    endDay = ui->endTimeEdit->date().day() - 1;

    qDebug() << startTimeStamp << endTimeStamp << startDay << endDay;

    timeStep = ui->timeStepSpinBox->value() * timeUnit[ui->timeStepComboBox->currentIndex()];

    qDebug() << allGrids << oneGrids;

    countThread->start();

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
