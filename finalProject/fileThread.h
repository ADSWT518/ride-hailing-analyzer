#ifndef FILETHREAD_H
#define FILETHREAD_H

#include <QThread>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTextBrowser>
#include <QDir>
#include <QVector>
#include <QProgressBar>
#include "dataForm.h"
#include "global.h"

class FileThread:public QThread
{
    Q_OBJECT

public:
    FileThread(QVector<QVector<orderDataForm>>*, QVector<gridDataForm>*, QProgressBar*);
    ~FileThread();

    void run() override;
    QStringList fileList;
    QDir directory;
    quint16 fileNum = 0;

signals:
    void resultReady(const QString &s);
    void fileNumChanged(quint16);

private:
    QVector<QVector<orderDataForm>>* mData;
    QVector<gridDataForm>* gData;
    QProgressBar* PB;
};

#endif // FILETHREAD_H
