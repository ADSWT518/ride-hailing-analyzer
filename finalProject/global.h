#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtGlobal>
#include <QVector>

#define dataPartsPerDay 5

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
extern QVector<quint32> orderCountVector;

extern bool allGrids;
extern bool oneGrids;

#endif// GLOBAL_H
