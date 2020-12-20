#ifndef FILETHREAD_H
#define FILETHREAD_H

#include "dataForm.h"
#include "global.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include <QTextBrowser>
#include <QThread>
#include <QVector>
#include <algorithm>

class FileThread : public QThread {
    Q_OBJECT

public:
    FileThread(QVector<QVector<orderDataForm>>*, QVector<QVector<coordinate>>*);
    ~FileThread();

    void run() override;
    QStringList fileList;
    QDir directory;
    quint16 fileNum = 0;

signals:
    void resultReady(const QString& s);
    void fileNumChanged(quint16);

private:
    QVector<QVector<orderDataForm>>* mainData;
    QVector<QVector<coordinate>>* gridData;
};

#endif// FILETHREAD_H
