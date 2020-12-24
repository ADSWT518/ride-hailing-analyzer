#include "countThread.h"
#include "global.h"
#include <QDebug>

bool isInGrid(coordinate point, QVector<QVector<coordinate>> gData, quint16 rNum, quint16 cNum)
{
//    if (point.lat >= gData[rNum - 1][0].lat && point.lat <= gData[rNum][0].lat && point.lng >= gData[0][cNum - 1].lng && point.lng <= gData[0][cNum].lng) {
//        qDebug() << '(' << point.lng << ',' << point.lat << ')';
//        qDebug() << gData[0][cNum - 1].lng << gData[0][cNum].lng << gData[rNum][0].lat << gData[rNum - 1][0].lat;
//    }

    return (point.lat >= gData[rNum][0].lat && point.lat <= gData[rNum - 1][0].lat && point.lng >= gData[0][cNum - 1].lng && point.lng <= gData[0][cNum].lng);
}


CountThread::CountThread(QVector<QVector<orderDataForm>>* mData, QVector<QVector<coordinate>>* gData) : mainData(mData), gridData(gData)
{
}

CountThread::~CountThread()
{
}

void CountThread::run()
{
    if (allGrids) {
        //整个成都的情况
        quint32 startIndex = 0;
        for (qint32 i = 0; i < mainData->at(startDay).size(); ++i) {
            if (mainData->at(startDay)[i].departure_time >= startTimeStamp) {
                qDebug() << "mainData->at(startDay)[i].departure_time" << mainData->at(startDay)[i].departure_time;
                startIndex = i;
                break;
            }
        }

        //TODO: debug

        quint32 curTimeStamp = startTimeStamp;
        quint16 curDay = startDay;

        qDebug() << "timeStep: " << timeStep << "startIndex: " << startIndex;
        orderCountVector.clear();
        orderCount = 0;
        for (qint32 i = startIndex; mainData->at(curDay)[i].departure_time <= endTimeStamp; ++i) {
            //qDebug() <<"mainData->at(curDay)[i].departure_time"<<mainData->at(curDay)[i].departure_time;

            //如果最后一组数据在达到timeStep之前就超过了endTimeStamp，那么舍弃它

            if (mainData->at(curDay)[i].departure_time <= curTimeStamp + timeStep) {
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
                if (curDay != 14) {
                    ++curDay;
                    i = -1;
                } else {
                    break;
                }
            }
        }
    } else {
        //某一个grid的情况
        quint32 startIndex = 0;
        for (qint32 i = 0; i < mainData->at(startDay).size(); ++i) {
            if (isInGrid(mainData->at(startDay)[i].orig, *gridData, rowNum, colNum) && mainData->at(startDay)[i].departure_time >= startTimeStamp) {
                //qDebug() << "mainData->at(startDay)[i].departure_time" << mainData->at(startDay)[i].departure_time;
                startIndex = i;
                break;
            }
        }

        //TODO: debug

        quint32 curTimeStamp = startTimeStamp;
        quint16 curDay = startDay;

        qDebug() << "timeStep: " << timeStep << "startIndex: " << startIndex;
        orderCountVector.clear();
        orderCount = 0;
        for (qint32 i = startIndex; mainData->at(curDay)[i].departure_time <= endTimeStamp; ++i) {
            //qDebug() <<"mainData->at(curDay)[i].departure_time"<<mainData->at(curDay)[i].departure_time;

            //如果最后一组数据在达到timeStep之前就超过了endTimeStamp，那么舍弃它

            if (mainData->at(curDay)[i].departure_time <= curTimeStamp + timeStep) {
                if (isInGrid(mainData->at(curDay)[i].orig, *gridData, rowNum, colNum)) {
                    ++orderCount;
                }
            } else {
                //qDebug() << "orderCount: " << orderCount;
                orderCountVector.append(orderCount);
                curTimeStamp += timeStep;
                orderCount = 0;
            }

            if (i == mainData->at(curDay).size() - 1) {
                if (curDay != 14) {
                    ++curDay;
                    i = -1;
                } else {
                    break;
                }
            }
        }
    }

    emit resultReady("Count successfully!");
}
