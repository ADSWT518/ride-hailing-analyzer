#include "fileThread.h"

FileThread::FileThread(QVector<QVector<orderDataForm>>* mData, QVector<QVector<coordinate>>* gData)
{
    mainData = mData;
    gridData = gData;
}

FileThread::~FileThread()
{
}


void FileThread::run()
{
    /* ... here is the expensive or blocking operation ... */

    QVector<orderDataForm> oneDayData;
    for (qint32 i = 0; i < fileList.size() - 1; ++i) {
        QFile file(directory.filePath(fileList[i].toLatin1()));

        if (i % dataPartsPerDay == 0) {
            oneDayData.clear();
        }

        if (file.open(QIODevice::ReadOnly)) {
            //qDebug() << file << '\n';
            QTextStream stream(&file);
            quint16 lineNum = 0;
            while (true) {
                QString line = stream.readLine();
                if (!lineNum) {
                    ++lineNum;
                    continue;
                }
                if (line.isEmpty()) {
                    break;
                }
                orderDataForm row(line.split(','));
                oneDayData.append(row);
            }
        }
        file.close();
        if (i % dataPartsPerDay == dataPartsPerDay - 1) {
            std::sort(oneDayData.begin(), oneDayData.end(), timeLessThan);
            mainData->append(oneDayData);
        }
        //qDebug()<<fileNum<<allFileNum;
        emit fileNumChanged(++fileNum);
    }

    QFile file(directory.filePath(fileList[fileList.size() - 1]));
    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << file << '\n';
        QTextStream stream(&file);
        quint16 lineNum = 0;
        QVector<coordinate> row;
        QVector<coordinate> row1;

        while (true) {
            QString line = stream.readLine();
            if (!lineNum) {
                ++lineNum;
                continue;
            }
            if (line.isEmpty()) {
                break;
            }

            quint16 grid_id = line.split(',')[0].trimmed().toUInt();
            coordinate v0(line.split(',')[1].trimmed().toDouble(), line.split(',')[2].trimmed().toDouble());
            coordinate v1(line.split(',')[3].trimmed().toDouble(), line.split(',')[4].trimmed().toDouble());
            coordinate v2(line.split(',')[5].trimmed().toDouble(), line.split(',')[6].trimmed().toDouble());
            coordinate v3(line.split(',')[7].trimmed().toDouble(), line.split(',')[8].trimmed().toDouble());

            gridData->operator[](10 - grid_id / 10)[grid_id % 10] = v3;
            if (grid_id % 10 == 9) {
                gridData->operator[](10 - grid_id / 10)[10] = v2;
            }
            if (grid_id >= 90) {
                gridData->operator[](0)[grid_id % 10] = v0;
                if (grid_id % 10 == 9) {
                    gridData->operator[](0)[10] = v1;
                }
            }
        }
    }
    file.close();
    emit fileNumChanged(++fileNum);
    //qDebug() <<mainData.size()<<mainData[0].size()<<mainData[0][0].size();
    //qDebug() <<gridData.size()<<gridData[0].size();
    emit resultReady("Load successfully.");
}
