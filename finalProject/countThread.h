#ifndef COUNTTHREAD_H
#define COUNTTHREAD_H

#include <QThread>
#include <QMutexLocker>
#include "dataForm.h"

class CountThread : public QThread {
    Q_OBJECT
    mutable QMutex m_mutex;
    bool m_cancel;
public:
    CountThread(QVector<QVector<orderDataForm>>*, QVector<QVector<coordinate>>*);
    ~CountThread();

    void cancel();
    bool isCanceled() const;

    void run() override;


signals:
    void resultReady(const QString& s);

private:
    QVector<QVector<orderDataForm>>* mainData;
    QVector<QVector<coordinate>>* gridData;

};

#endif // COUNTTHREAD_H
