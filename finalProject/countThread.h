#ifndef COUNTTHREAD_H
#define COUNTTHREAD_H

#include <QThread>
#include "dataForm.h"

class CountThread : public QThread {
    Q_OBJECT

public:
    CountThread(QVector<QVector<orderDataForm>>*, QVector<QVector<coordinate>>*);
    ~CountThread();

    void run() override;


signals:
    void resultReady(const QString& s);

private:
    QVector<QVector<orderDataForm>>* mainData;
    QVector<QVector<coordinate>>* gridData;

};

#endif // COUNTTHREAD_H
