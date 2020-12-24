#include "global.h"

quint16 fileNum = 0;
quint16 allFileNum = 0;

quint32 startTimeStamp = 0;
quint32 endTimeStamp = 0;
quint32 curTimeStamp = 0;
quint16 startDay = 0;
quint16 endDay = 0;
quint16 curDay = 0;
quint32 timeStep = 0;

const quint32 timeUnit[3] = {60, 3600, 86400};
const quint16 timeUnitMax[3] = {59, 23, 15};

quint32 orderCount = 0;
QVector<qint32> orderCountVector;

bool allGrids = 0;
bool oneGrid = 0;

quint16 rowNum = 0;
quint16 colNum = 0;
