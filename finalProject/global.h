#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtGlobal>
#include <QVector>

#define dataPartsPerDay 5
#define minPointNumInChart 10

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
extern QVector<qint32> orderCountVector;

extern bool allGrids;
extern bool oneGrid;

extern quint16 rowNum;
extern quint16 colNum;

#endif// GLOBAL_H
