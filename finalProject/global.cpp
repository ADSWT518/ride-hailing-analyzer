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
//(0,15] (15, 30], (30, 45], (45, 90], (90, +∞)
QVector<qint32> feesCountVector(5);
//(0,5] (5, 10], (10, 20], (20, 30], (30, +∞)

bool order_id_selected = 0;
const bool departure_time_selected = 1;
bool end_time_selected = 0;
bool orig_selected = 0;
bool dest_selected = 0;
bool fee_selected = 0;

bool allGrids = 1;
bool oneGrid = 0;

quint16 rowNum = 0;
quint16 colNum = 0;

bool displaySTButtonClicked = 0;
bool displayTimeButtonClicked = 0;
bool displayFeesButtonClicked = 0;

double totalRevenue = 0;

QTime totalTime;

bool needToReload = 0;//是否需要重新载入文件（即QCheckBox有没有改变）
