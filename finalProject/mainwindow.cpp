#include "mainwindow.h"
#include "countThread.h"
#include "fileThread.h"
#include "global.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <iostream>
#include <numeric>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
    setupSignalSlots();

    gridData.resize(11);
    for (quint16 i = 0; i < 11; ++i) {
        gridData[i].resize(11);
    }
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
    connect(ui->allGridRadioButton, &QRadioButton::clicked, ui->rowSpinBox, &QWidget::setDisabled);
    connect(ui->allGridRadioButton, &QRadioButton::clicked, ui->columnSpinBox, &QWidget::setDisabled);
    connect(ui->allGridRadioButton, &QRadioButton::clicked, ui->label_8, &QWidget::setDisabled);
    connect(ui->allGridRadioButton, &QRadioButton::clicked, ui->label_9, &QWidget::setDisabled);
    connect(ui->oneGridRadioButton, &QRadioButton::clicked, ui->rowSpinBox, &QWidget::setEnabled);
    connect(ui->oneGridRadioButton, &QRadioButton::clicked, ui->columnSpinBox, &QWidget::setEnabled);
    connect(ui->oneGridRadioButton, &QRadioButton::clicked, ui->label_8, &QWidget::setEnabled);
    connect(ui->oneGridRadioButton, &QRadioButton::clicked, ui->label_9, &QWidget::setEnabled);

    //TODO: debug
    connect(ui->timeStepSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            [=](int i) {
                if (displaySTButtonClicked || displayTimeButtonClicked || displayFeesButtonClicked) {
                    displaySTDemand();
                }
            });
    connect(ui->timeStepComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index) {
                if (displaySTButtonClicked || displayTimeButtonClicked || displayFeesButtonClicked) {
                    displaySTDemand();
                }
            });
    connect(ui->timeStepComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index) {
                ui->timeStepSpinBox->setMaximum(timeUnitMax[index]);
            });
}

void MainWindow::Lagrange_interpolation(QVector<qint64>& ocVector, QVector<qint64>& tVector, quint32 tStep)
{
    quint32 size = ocVector.size();

    for (quint32 i = 0; i < size - 1; i++) {
        double res = 0;
        for (quint32 j = 0; j < size; j++) {
            double up = 1, down = 1;
            for (quint32 k = 0; k < size; k++) {
                if (k == j)
                    continue;
                up *= (startTimeStamp + tStep * i + tStep / 2) - tVector[k];
                down *= tVector[j] - tVector[k];
            }
            res += ocVector[j] * up / down;
            //qDebug() << up << down;
        }
        qDebug() << res;
        ocVector.insert(ocVector.begin() + (2 * i + 1), res);
        tVector.append(startTimeStamp + tStep * i + tStep / 2);
    }

    //    std::sort(ocVector.begin(), ocVector.end());
    std::sort(tVector.begin(), tVector.end());

    //    qDebug() << "ocVector:" << ocVector;
    //    qDebug() << "tVecotr:" << tVector;
    qDebug() << "Lagrange!";
}


void MainWindow::loadFile()
{
    FileThread* fileThread = new FileThread(&mainData, &gridData);
    connect(fileThread, &FileThread::resultReady, this, &MainWindow::handleFileResults);
    connect(fileThread, &FileThread::finished, fileThread, &QObject::deleteLater);
    connect(fileThread, &FileThread::fileNumChanged, this, &MainWindow::setProgressBar);

    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "../",
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks)
                              .toLatin1();
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

//    for (int i = 0; i < gridData.size(); ++i) {
//        for (int j = 0; j < gridData.at(0).size(); ++j) {
//            std::cout << '(' << gridData[i][j].lng << ',' << gridData[i][j].lat << ')';
//        }
//        std::cout << '\n';
//    }
}

void MainWindow::setProgressBar(quint16 fileNum)
{
    ui->UIprogressBar->setValue(fileNum);
}

void MainWindow::allGridsSelected()
{
    allGrids = true;
    oneGrid = false;
}

void MainWindow::oneGridSelected()
{
    oneGrid = true;
    allGrids = false;
}

void MainWindow::handleSTCountResults(QString r)
{
    qDebug() << r;

    if (displaySTButtonClicked) {
        chart->removeAllSeries();
        chart->removeAxis(axisX);
        chart->removeAxis(axisY);
    }

    //qDebug() <<"chart->series().size()"<<chart->series().size();

    if (allGrids) {
        //All grids in Chengdu are selected.
        chart->setTitle("The number of orders in Chengdu over time");

    } else if (oneGrid) {
        //Only one grid is selected.
        chart->setTitle("The number of orders in one grid over time");

    } else {
        qDebug() << "Please select grid area.";
    }

    QLineSeries* orderNumSeries = new QLineSeries();
    //orderNumSeries->clear();

    QVector<qint64> timeVector;

    for (qint32 i = 0; i < orderCountVector.size(); ++i) {
        timeVector.push_back(startTimeStamp + timeStep * i);
    }

    quint32 tStep = timeStep;
    while (orderCountVector.size() <= minPointNumInChart) {
        //when only a few data points are selected, use interpolation
        Lagrange_interpolation(orderCountVector, timeVector, tStep);
        tStep /= 2;
    }

    //qDebug() << "orderCountVector:" << orderCountVector;
    //qDebug() << "timeVector:" << timeVector;

    qDebug() << orderCountVector.size() << timeVector.size();
    for (qint32 i = 0; i < orderCountVector.size(); ++i) {
        QDateTime dt;
        dt.setSecsSinceEpoch(timeVector[i]);
        orderNumSeries->append(dt.toMSecsSinceEpoch(), orderCountVector[i]);
        //qDebug() <<'('<<startTimeStamp + timeStep * i<<','<< orderCountVector[i]<<')';
    }
    chart->addSeries(orderNumSeries);

    qDebug() << "orderCountVector.size():" << orderCountVector.size();
    //qDebug() <<"orderCountVector"<<orderCountVector;
    qDebug() << "sum of orderCountVector:" << std::accumulate(orderCountVector.begin(), orderCountVector.end(), 0);

    axisX->setFormat("dd-MM-yyyy h:mm");
    QDateTime dt;
    dt.setSecsSinceEpoch(timeVector[0]);
    QDateTime min = dt;
    dt.setSecsSinceEpoch(timeVector.back());
    QDateTime max = dt;
    axisX->setRange(min, max);

    axisY->setRange(0, *std::max_element(orderCountVector.begin(), orderCountVector.end()));
    axisY->setTitleText("num");
    //axisY->setLabelFormat("%d");
    //axisY->setTickCount(14);
    //axisY->setMinorTickCount(5);

    chart->setAxisX(axisX, orderNumSeries);
    chart->setAxisY(axisY, orderNumSeries);


    ui->graphicsView->setChart(chart);
}

void MainWindow::handleTimeCountResults(QString r)
{
    qDebug() << r;

    //if (displaySTButtonClicked) {
        chart->removeAllSeries();
        chart->removeAxis(axisX);
        chart->removeAxis(axisY);
    //}

    if (allGrids) {
        //All grids in Chengdu are selected.
        chart->setTitle("Travel time in Chengdu");
    } else if (oneGrid) {
        //Only one grid is selected.
        chart->setTitle("Travel time in one grid");
    } else {
        qDebug() << "Please select grid area.";
    }

    QPieSeries* travelTimeSeries = new QPieSeries();
    //orderNumSeries->clea

    travelTimeSeries->append("0-15min", travelTimeCountVector[0]);
    travelTimeSeries->append("15-30min", travelTimeCountVector[1]);
    travelTimeSeries->append("30-45min", travelTimeCountVector[2]);
    travelTimeSeries->append("45-90min", travelTimeCountVector[3]);
    travelTimeSeries->append(">90min", travelTimeCountVector[4]);

    travelTimeSeries->setLabelsVisible(true);
    travelTimeSeries->setUseOpenGL(true);

    chart->addSeries(travelTimeSeries);


    ui->graphicsView->setChart(chart);
}

void MainWindow::handleFeesCountResults(QString r)
{
    qDebug() <<r;

    qDebug() << r;

    //if (displaySTButtonClicked) {
        chart->removeAllSeries();
        chart->removeAxis(axisX);
        chart->removeAxis(axisY);
    //}

    if (allGrids) {
        //All grids in Chengdu are selected.
        chart->setTitle("Order fees in Chengdu during this time");
    } else if (oneGrid) {
        //Only one grid is selected.
        chart->setTitle("Order fees in one grid during this time");
    } else {
        qDebug() << "Please select grid area.";
    }

    QPieSeries* travelTimeSeries = new QPieSeries();
    //orderNumSeries->clea


    travelTimeSeries->append("0-5￥", feesCountVector[0]);
    travelTimeSeries->append("5-10￥", feesCountVector[1]);
    travelTimeSeries->append("10-20￥", feesCountVector[2]);
    travelTimeSeries->append("20-30￥", feesCountVector[3]);
    travelTimeSeries->append(">30￥", feesCountVector[4]);

    travelTimeSeries->setLabelsVisible(true);
    travelTimeSeries->setUseOpenGL(true);

    chart->addSeries(travelTimeSeries);


    ui->graphicsView->setChart(chart);

}

void MainWindow::displaySTDemand()
{
    if (!fileLoaded) {
        QMessageBox::warning(this, "Warning!", "Please load file fist!");
        return;
    }

    displaySTButtonClicked = 1;
    displayTimeButtonClicked = 0;
    displayFeesButtonClicked = 0;


    if (oneGrid) {
        rowNum = ui->rowSpinBox->value();
        colNum = ui->columnSpinBox->value();
        qDebug() << "a grid area is selected. (" << rowNum << ',' << colNum << ')';
    } else if (allGrids) {
        qDebug() << "All grids in Chengdu is selected.";
    } else {
        qDebug() << "Please select grid area.";
        return;
    }

    CountThread* countThread = new CountThread(&mainData, &gridData);
    connect(countThread, &CountThread::resultReady, this, &MainWindow::handleSTCountResults);
    connect(countThread, &CountThread::finished, countThread, &QObject::deleteLater);


    startTimeStamp = ui->startTimeEdit->dateTime().toSecsSinceEpoch();
    endTimeStamp = ui->endTimeEdit->dateTime().toSecsSinceEpoch();
    startDay = ui->startTimeEdit->date().day() - 1;
    endDay = ui->endTimeEdit->date().day() - 1;

    qDebug() << startTimeStamp << endTimeStamp << startDay << endDay;

    timeStep = ui->timeStepSpinBox->value() * timeUnit[ui->timeStepComboBox->currentIndex()];

    qDebug() << allGrids << oneGrid;

    countThread->start();
}

void MainWindow::displayTravelTime()
{
    if (!fileLoaded) {
        QMessageBox::warning(this, "Warning!", "Please load file fist!");
        return;
    }

    displaySTButtonClicked = 0;
    displayTimeButtonClicked = 1;
    displayFeesButtonClicked = 0;

    if (oneGrid) {
        rowNum = ui->rowSpinBox->value();
        colNum = ui->columnSpinBox->value();
        qDebug() << "a grid area is selected. (" << rowNum << ',' << colNum << ')';
    } else if (allGrids) {
        qDebug() << "All grids in Chengdu is selected.";
    } else {
        qDebug() << "Please select grid area.";
        return;
    }

    CountThread* countThread = new CountThread(&mainData, &gridData);
    connect(countThread, &CountThread::resultReady, this, &MainWindow::handleTimeCountResults);
    connect(countThread, &CountThread::finished, countThread, &QObject::deleteLater);

    startTimeStamp = ui->startTimeEdit->dateTime().toSecsSinceEpoch();
    endTimeStamp = ui->endTimeEdit->dateTime().toSecsSinceEpoch();
    startDay = ui->startTimeEdit->date().day() - 1;
    endDay = ui->endTimeEdit->date().day() - 1;

    qDebug() << startTimeStamp << endTimeStamp << startDay << endDay;

    timeStep = ui->timeStepSpinBox->value() * timeUnit[ui->timeStepComboBox->currentIndex()];

    qDebug() << allGrids << oneGrid;

    countThread->start();
}

void MainWindow::displayOrderFees()
{
    if (!fileLoaded) {
        QMessageBox::warning(this, "Warning!", "Please load file fist!");
        return;
    }

    displaySTButtonClicked = 0;
    displayTimeButtonClicked = 0;
    displayFeesButtonClicked = 1;

    if (oneGrid) {
        rowNum = ui->rowSpinBox->value();
        colNum = ui->columnSpinBox->value();
        qDebug() << "a grid area is selected. (" << rowNum << ',' << colNum << ')';
    } else if (allGrids) {
        qDebug() << "All grids in Chengdu is selected.";
    } else {
        qDebug() << "Please select grid area.";
        return;
    }

    CountThread* countThread = new CountThread(&mainData, &gridData);
    connect(countThread, &CountThread::resultReady, this, &MainWindow::handleFeesCountResults);
    connect(countThread, &CountThread::finished, countThread, &QObject::deleteLater);

    startTimeStamp = ui->startTimeEdit->dateTime().toSecsSinceEpoch();
    endTimeStamp = ui->endTimeEdit->dateTime().toSecsSinceEpoch();
    startDay = ui->startTimeEdit->date().day() - 1;
    endDay = ui->endTimeEdit->date().day() - 1;

    qDebug() << startTimeStamp << endTimeStamp << startDay << endDay;

    timeStep = ui->timeStepSpinBox->value() * timeUnit[ui->timeStepComboBox->currentIndex()];

    qDebug() << allGrids << oneGrid;

    countThread->start();
}
