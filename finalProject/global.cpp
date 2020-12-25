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
QVector<qint64> orderCountVector;
QVector<qint32> travelTimeCountVector(5);
//(0,10] (10, 30], (30, 60], (60, 120], (120, +∞)
QVector<qint32> feesCountVector(5);
//(0,10] (10, 25], (25, 50], (50, 100], (100, +∞)

bool allGrids = 0;
bool oneGrid = 0;

quint16 rowNum = 0;
quint16 colNum = 0;

bool displaySTButtonClicked = 0;
bool displayTimeButtonClicked = 0;
bool displayFeesButtonClicked = 0;
