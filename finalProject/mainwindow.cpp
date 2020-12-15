#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

    displaySTAction = new QAction(tr("&Spatio-temporal demand"), this);
    displayTravelTimeAction = new QAction(tr("&Travel time"), this);
    displayFeeAction = new QAction(tr("&Fee"), this);

    displayMenu->addAction(displaySTAction);
    displayMenu->addAction(displayTravelTimeAction);
    displayMenu->addAction(displayFeeAction);

    openAction->setCheckable(false);
    //openAction->setChecked(false);

    menuBar()->addMenu(loadMenu);
    menuBar()->addMenu(displayMenu);

}

void MainWindow::setupSignalSlots()
{
    connect(openAction,SIGNAL(triggered()),this,SLOT(loadFile()));
    connect(ui->loadDataButton, SIGNAL(clicked()), this, SLOT(loadFile()));

}

void MainWindow::loadFile()
{

    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "../Dataset-CS241-2020/",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    //qDebug() <<dirName;

    QDir dir(dirName);
    QStringList nameFilters;
    nameFilters << "*.csv";
    QStringList fileList = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);

    //qDebug() <<fileList;

    QList<QList<double>> oneDayData;
    for(int i = 0;i<fileList.size()-1;++i){
        QFile file(dir.filePath(fileList[i]));

        if(i % 5 == 0){
            oneDayData.clear();
        }

        if(file.open(QIODevice::ReadOnly)){
            qDebug()<<file<<'\n';
            QTextStream stream(&file);
            int lineNum = 0;
            while(true){
                QString line = stream.readLine();
                if(!lineNum){
                    ++lineNum;
                    continue;
                }
                if(line.isEmpty()){
                    break;
                }
                QList<double> row;
                for(auto n:line.split(',')){
                    row.append(n.trimmed().toDouble());
                }
                oneDayData.append(row);
            }
        }
        file.close();
        if(i % 5 == 4){
            mainData.append(oneDayData);
        }
    }


    QFile file(dir.filePath(fileList[fileList.size()-1]));
    if(file.open(QIODevice::ReadOnly)){
        qDebug()<<file<<'\n';
        QTextStream stream(&file);
        int lineNum = 0;
        while(true){
            QString line = stream.readLine();
            if(!lineNum){
                ++lineNum;
                continue;
            }
            if(line.isEmpty()){
                break;
            }
            QList<double> row;
            for(auto n:line.split(',')){
                row.append(n.trimmed().toDouble());
            }
            gridData.append(row);
        }
    }
    file.close();
    //qDebug() <<mainData.size()<<mainData[0].size()<<mainData[0][0].size();
    //qDebug() <<gridData.size()<<gridData[0].size();
}





