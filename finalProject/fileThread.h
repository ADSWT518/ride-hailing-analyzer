#ifndef FILETHREAD_H
#define FILETHREAD_H

#include <QThread>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTextBrowser>
#include <QDir>
#include <QVector>
#include "dataForm.h"

extern quint16 fileNum;
extern quint16 allFileNum;

class FileThread:public QThread
{
    Q_OBJECT

public:
    FileThread(QVector<QVector<orderDataForm>>*, QVector<gridDataForm>*);
    ~FileThread();

    void run() override;
    QStringList fileList;
    QDir directory;
    quint16 fileNum = 0;

signals:
    void resultReady(const QString &s);
    void sendFileNum(quint16);

private:
    QVector<QVector<orderDataForm>>* mData;
    QVector<gridDataForm>* gData;
};

#endif // FILETHREAD_H
