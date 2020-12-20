#include "countThread.h"
#include "global.h"
#include <QDebug>

CountThread::CountThread(QVector<QVector<orderDataForm>>* mData)
{
    mainData = mData;
}

CountThread::~CountThread()
{
}

void CountThread::run()
{
    if (allGrids) {
        quint32 startIndex = 0;
        for (qint32 i = 0; i < mainData->at(startDay).size(); ++i) {
            if (mainData->at(startDay)[i].departure_time >= startTimeStamp) {
                qDebug()<<"mainData->at(startDay)[i].departure_time"<<mainData->at(startDay)[i].departure_time;
                startIndex = i;
                break;
            }
        }

        //TODO: debug

        quint32 curTimeStamp = startTimeStamp;
        quint16 curDay = startDay;

        qDebug() <<"timeStep: "<<timeStep<<"startIndex: "<<startIndex;
        orderCountVector.clear();
        orderCount = 0;
        for (qint32 i = startIndex; mainData->at(curDay)[i].departure_time <= endTimeStamp; ++i) {
            //qDebug() <<"mainData->at(curDay)[i].departure_time"<<mainData->at(curDay)[i].departure_time;

            //如果最后一组数据在达到timeStep之前就超过了endTimeStamp，那么舍弃它

            if (mainData->at(curDay)[i].departure_time < curTimeStamp + timeStep) {
                ++orderCount;
            } else {
                //qDebug() << "orderCount: " << orderCount;
                orderCountVector.append(orderCount);
                //emit orderCountRefresh();
                //orderNumSeries->append(curTimeStamp, orderCount);
                curTimeStamp += timeStep;
                orderCount = 0;
            }

            if (i == mainData->at(curDay).size() - 1) {
                if(curDay != 14){
                    ++curDay;
                    i = -1;
                }else{
                    break;
                }

            }
        }
    } else {

    }

    emit resultReady("Count successfully!");
}
