#ifndef PROGRESSBARTHREAD_H
#define PROGRESSBARTHREAD_H

#include <QThread>
#include <QProgressBar>

class ProgressBarThread:public QThread
{
    Q_OBJECT

public:
    ProgressBarThread(QProgressBar*);
    ~ProgressBarThread();

    void run() override;

    QProgressBar* PB;


signals:
    void resultReady(const QString &s);

private:

};


#endif // PROGRESSBARTHREAD_H
