#ifndef COUNTTHREAD_H
#define COUNTTHREAD_H

#include <QThread>
#include "dataForm.h"

class CountThread : public QThread {
    Q_OBJECT

public:
    CountThread(QVector<QVector<orderDataForm>>*);
    ~CountThread();

    void run() override;


signals:
    void resultReady(const QString& s);
    void orderCountRefresh();

private:
    QVector<QVector<orderDataForm>>* mainData;


};

#endif // COUNTTHREAD_H
