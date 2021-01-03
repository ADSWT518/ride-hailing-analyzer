#include "mainwindow.h"
#include "countThread.h"
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

    displayTravelTimeAction->setDisabled(true);
    displayOrderFeesAction->setDisabled(true);

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
    connect(ui->cancelButton, &QPushButton::clicked, this, &MainWindow::cancelLoadFile);

    connect(displaySTDemandAction, &QAction::triggered, this, &MainWindow::displaySTDemand);
    connect(displaySTDemandAction, &QAction::triggered, ui->lineEdit, &QLineEdit::clear);
    connect(ui->STDemandButton, &QPushButton::clicked, this, &MainWindow::displaySTDemand);
    connect(ui->STDemandButton, &QPushButton::clicked, ui->lineEdit, &QLineEdit::clear);
    connect(displayTravelTimeAction, &QAction::triggered, this, &MainWindow::displayTravelTime);
    connect(displayTravelTimeAction, &QAction::triggered, ui->lineEdit, &QLineEdit::clear);
    connect(ui->travelTimeButton, &QPushButton::clicked, this, &MainWindow::displayTravelTime);
    connect(ui->travelTimeButton, &QPushButton::clicked, ui->lineEdit, &QLineEdit::clear);
    connect(displayOrderFeesAction, &QAction::triggered, this, &MainWindow::displayOrderFees);
    connect(ui->orderFeesButton, &QPushButton::clicked, this, &MainWindow::displayOrderFees);

    connect(ui->orderIDBox, &QCheckBox::stateChanged, this, &MainWindow::orderIDChanged);
    //    connect(ui->depTimeBox, &QCheckBox::stateChanged, this, &MainWindow::depTimechanged);
    connect(ui->endTimeBox, &QCheckBox::stateChanged, this, &MainWindow::endTimeChanged);
    connect(ui->origBox, &QCheckBox::stateChanged, this, &MainWindow::origChanged);
    connect(ui->destBox, &QCheckBox::stateChanged, this, &MainWindow::destChanged);
    connect(ui->feeBox, &QCheckBox::stateChanged, this, &MainWindow::feeChanged);


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
//        qDebug() << res;
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
    totalTime.start();

    if (m_currentFileThread) {
        qDebug() << "???";
        m_currentFileThread->cancel();
    }

    mainData.clear();
    gridData.clear();
    gridData.resize(11);
    for (quint16 i = 0; i < 11; ++i) {
        gridData[i].resize(11);
    }

    FileThread* fileThread = new FileThread(&mainData, &gridData);
    connect(fileThread, &FileThread::resultReady, this, &MainWindow::handleFileResults);
    connect(fileThread, &FileThread::finished, fileThread, &QObject::deleteLater);
    connect(fileThread, &FileThread::fileNumChanged, this, &MainWindow::setProgressBar);
    connect(fileThread, &FileThread::destroyed, this, &MainWindow::fileThreadDestroy);
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
    m_currentFileThread = fileThread;
    ui->statusbar->showMessage(tr("Loading..."));
    fileThread->start();
}

void MainWindow::cancelLoadFile()
{
    if (m_currentFileThread) {
        qDebug() << "cancel";
        m_currentFileThread->cancel();
        ui->UIprogressBar->setValue(0);
    }
}

void MainWindow::handleFileResults(QString r)
{
    QString status= r;
    if (r == "Load successfully.") {
        status += " Total time is " + QString::number(totalTime.elapsed() / 1000.0) + 's';
    }
    ui->statusbar->showMessage(tr(status.toLocal8Bit().data()));
    if (r == "Load successfully.") {
        fileLoaded = true;
    }
    needToReload = false;
}

void MainWindow::setProgressBar(quint16 fileNum)
{
    ui->UIprogressBar->setValue(fileNum);
}


void MainWindow::orderIDChanged(quint32 state)
{
    order_id_selected = state;
}
//void MainWindow::depTimechanged(quint32 state)
//{
//    departure_time_selected = state;
//}
void MainWindow::endTimeChanged(quint32 state)
{
    end_time_selected = state;
    needToReload = state;
    ui->travelTimeButton->setEnabled(end_time_selected);
    displayTravelTimeAction->setEnabled(end_time_selected);
}
void MainWindow::origChanged(quint32 state)
{
    orig_selected = state;
    needToReload = state;
    ui->allGridRadioButton->setEnabled(orig_selected);
    if (orig_selected) {
        ui->allGridRadioButton->setCheckable(false);
        ui->allGridRadioButton->setCheckable(true);
    } else {
        ui->allGridRadioButton->setChecked(true);
    }

    allGrids = !orig_selected;
    qDebug() << allGrids;
    ui->oneGridRadioButton->setEnabled(orig_selected);
    ui->rowSpinBox->setEnabled(orig_selected);
    ui->columnSpinBox->setEnabled(orig_selected);
    ui->label_8->setEnabled(orig_selected);
    ui->label_9->setEnabled(orig_selected);
}
void MainWindow::destChanged(quint32 state)
{
    dest_selected = state;
}
void MainWindow::feeChanged(quint32 state)
{
    fee_selected = state;
    needToReload = state;

    ui->orderFeesButton->setEnabled(fee_selected);
    displayOrderFeesAction->setEnabled(fee_selected);
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
    if (r == "Plot successfully!") {
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
            QMessageBox::warning(this, "Warning!", "Please select grid area.");
            return;
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

//        qDebug() << orderCountVector.size() << timeVector.size();
        for (qint32 i = 0; i < orderCountVector.size(); ++i) {
            QDateTime dt;
            dt.setSecsSinceEpoch(timeVector[i]);
            orderNumSeries->append(dt.toMSecsSinceEpoch(), orderCountVector[i]);
            //qDebug() <<'('<<startTimeStamp + timeStep * i<<','<< orderCountVector[i]<<')';
        }
        chart->addSeries(orderNumSeries);

//        qDebug() << "orderCountVector.size():" << orderCountVector.size();
        //qDebug() <<"orderCountVector"<<orderCountVector;
//        qDebug() << "sum of orderCountVector:" << std::accumulate(orderCountVector.begin(), orderCountVector.end(), 0);

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

        QString status = r + " Total time is " + QString::number(totalTime.elapsed() / 1000.0) + 's';
        ui->statusbar->showMessage(tr(status.toLocal8Bit().data()));
    }
}

void MainWindow::handleTimeCountResults(QString r)
{
//    qDebug() << r;
    if (r == "Plot successfully!") {
        //if (displaySTButtonClicked) {
        chart->removeAllSeries();
        chart->removeAxis(axisX);
        chart->removeAxis(axisY);
        //}
        chart->setAnimationDuration(QChart::AllAnimations);
        if (allGrids) {
            //All grids in Chengdu are selected.
            chart->setTitle("Travel time in Chengdu");
        } else if (oneGrid) {
            //Only one grid is selected.
            chart->setTitle("Travel time in one grid");
        } else {
            QMessageBox::warning(this, "Warning!", "Please select grid area.");
            return;
        }

        QPieSeries* travelTimeSeries = new QPieSeries();

        travelTimeSeries->append("0-15min", travelTimeCountVector[0]);
        travelTimeSeries->append("15-30min", travelTimeCountVector[1]);
        travelTimeSeries->append("30-45min", travelTimeCountVector[2]);
        travelTimeSeries->append("45-90min", travelTimeCountVector[3]);
        travelTimeSeries->append(">90min", travelTimeCountVector[4]);

        travelTimeSeries->setLabelsVisible(true);
        travelTimeSeries->setUseOpenGL(true);

        chart->addSeries(travelTimeSeries);

        ui->graphicsView->setChart(chart);
        QString status = r + " Total time is " + QString::number(totalTime.elapsed() / 1000.0) + 's';
        ui->statusbar->showMessage(tr(status.toLocal8Bit().data()));
    }
}

void MainWindow::handleFeesCountResults(QString r)
{
    qDebug() << r;

    if (r == "Plot successfully!") {
        ui->lineEdit->setText(QString::number(totalRevenue, 'f', 2));

        //if (displaySTButtonClicked) {
        chart->removeAllSeries();
        chart->removeAxis(axisX);
        chart->removeAxis(axisY);
        //}
        chart->setAnimationDuration(QChart::AllAnimations);

        if (allGrids) {
            //All grids in Chengdu are selected.
            chart->setTitle("Order fees in Chengdu during this time");
        } else if (oneGrid) {
            //Only one grid is selected.
            chart->setTitle("Order fees in one grid during this time");
        } else {
            QMessageBox::warning(this, "Warning!", "Please select grid area.");
            return;
        }

        QPieSeries* travelTimeSeries = new QPieSeries();

        travelTimeSeries->append("0-5￥", feesCountVector[0]);
        travelTimeSeries->append("5-10￥", feesCountVector[1]);
        travelTimeSeries->append("10-20￥", feesCountVector[2]);
        travelTimeSeries->append("20-30￥", feesCountVector[3]);
        travelTimeSeries->append(">30￥", feesCountVector[4]);

        travelTimeSeries->setLabelsVisible(true);
        travelTimeSeries->setUseOpenGL(true);

        chart->addSeries(travelTimeSeries);

        ui->graphicsView->setChart(chart);
        QString status = r + " Total time is " + QString::number(totalTime.elapsed() / 1000.0) + 's';
        ui->statusbar->showMessage(tr(status.toLocal8Bit().data()));
    }
}

void MainWindow::displaySTDemand()
{
    if (!fileLoaded) {
        QMessageBox::warning(this, "Warning!", "Please load file fist!");
        return;
    }

    if(needToReload){
        QMessageBox::warning(this, "Warning!", "Please reload file!");
        return;
    }

    if (m_currentCountThread) {
//        qDebug() << "???";
        m_currentCountThread->cancel();
    }
    orderCountVector.clear();

    ui->label_10->setEnabled(false);
    ui->label_11->setEnabled(false);
    ui->lineEdit->setEnabled(false);

    displaySTButtonClicked = 1;
    displayTimeButtonClicked = 0;
    displayFeesButtonClicked = 0;


    if (oneGrid) {
        rowNum = ui->rowSpinBox->value();
        colNum = ui->columnSpinBox->value();
//        qDebug() << "a grid area is selected. (" << rowNum << ',' << colNum << ')';
    } else if (allGrids) {
//        qDebug() << "All grids in Chengdu is selected.";
    } else {
        QMessageBox::warning(this, "Warning!", "Please select grid area.");
//        qDebug() << "Please select grid area.";
        return;
    }

    totalTime.restart();

    ui->statusbar->showMessage(tr("Analysing..."));

    CountThread* countThread = new CountThread(&mainData, &gridData);
    connect(countThread, &CountThread::resultReady, this, &MainWindow::handleSTCountResults);
    connect(countThread, &CountThread::finished, countThread, &QObject::deleteLater);
    connect(countThread, &FileThread::destroyed, this, &MainWindow::countThreadDestroy);


    startTimeStamp = ui->startTimeEdit->dateTime().toSecsSinceEpoch();
    endTimeStamp = ui->endTimeEdit->dateTime().toSecsSinceEpoch();
    startDay = ui->startTimeEdit->date().day() - 1;
    endDay = ui->endTimeEdit->date().day() - 1;

//    qDebug() << startTimeStamp << endTimeStamp << startDay << endDay;

    timeStep = ui->timeStepSpinBox->value() * timeUnit[ui->timeStepComboBox->currentIndex()];

    qDebug() << allGrids << oneGrid;
    m_currentCountThread = countThread;
    countThread->start();
}

void MainWindow::displayTravelTime()
{
    if (!fileLoaded) {
        QMessageBox::warning(this, "Warning!", "Please load file fist!");
        return;
    }

    if(needToReload){
        QMessageBox::warning(this, "Warning!", "Please reload file!");
        return;
    }

    ui->label_10->setEnabled(false);
    ui->label_11->setEnabled(false);
    ui->lineEdit->setEnabled(false);

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
        QMessageBox::warning(this, "Warning!", "Please load file fist!");
        return;
    }

    totalTime.restart();
    ui->statusbar->showMessage(tr("Analysing..."));

    CountThread* countThread = new CountThread(&mainData, &gridData);
    connect(countThread, &CountThread::resultReady, this, &MainWindow::handleTimeCountResults);
    connect(countThread, &CountThread::finished, countThread, &QObject::deleteLater);

    startTimeStamp = ui->startTimeEdit->dateTime().toSecsSinceEpoch();
    endTimeStamp = ui->endTimeEdit->dateTime().toSecsSinceEpoch();
    startDay = ui->startTimeEdit->date().day() - 1;
    endDay = ui->endTimeEdit->date().day() - 1;

//    qDebug() << startTimeStamp << endTimeStamp << startDay << endDay;

    timeStep = ui->timeStepSpinBox->value() * timeUnit[ui->timeStepComboBox->currentIndex()];

    qDebug() << allGrids << oneGrid;
    qDebug() <<displayTimeButtonClicked;
    countThread->start();
}

void MainWindow::displayOrderFees()
{
    if (!fileLoaded) {
        QMessageBox::warning(this, "Warning!", "Please load file fist!");
        return;
    }

    if(needToReload){
        QMessageBox::warning(this, "Warning!", "Please reload file!");
        return;
    }

    totalRevenue = 0;
    ui->label_10->setEnabled(true);
    ui->label_11->setEnabled(true);
    ui->lineEdit->setEnabled(true);

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
        QMessageBox::warning(this, "Warning!", "Please select grid area.");
        return;
    }

    totalTime.restart();
    ui->statusbar->showMessage(tr("Analysing..."));

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

void MainWindow::fileThreadDestroy(QObject* obj)
{
    if (m_currentFileThread == obj) {
        m_currentFileThread = nullptr;
    }
}

void MainWindow::countThreadDestroy(QObject* obj)
{
    if (m_currentCountThread == obj) {
        m_currentCountThread = nullptr;
    }
}
