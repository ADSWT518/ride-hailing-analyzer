#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtGlobal>
#include <QVector>

#define dataPartsPerDay 5
#define minPointNumInChart 8

extern quint32 startTimeStamp;
extern quint32 endTimeStamp;
extern quint32 curTimeStamp;
extern quint16 startDay;
extern quint16 endDay;
extern quint16 curDay;
extern quint32 timeStep;

extern const quint32 timeUnit[3];
extern const quint16 timeUnitMax[3];

extern quint32 orderCount;
extern QVector<qint64> orderCountVector;
extern QVector<qint32> travelTimeCountVector;
extern QVector<qint32> feesCountVector;

extern bool allGrids;
extern bool oneGrid;

extern quint16 rowNum;
extern quint16 colNum;

extern bool displaySTButtonClicked;
extern bool displayTimeButtonClicked;
extern bool displayFeesButtonClicked;

#endif// GLOBAL_H
