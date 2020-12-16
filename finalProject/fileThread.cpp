#include "fileThread.h"

FileThread::FileThread(QVector<QVector<orderDataForm>>* mainData, QVector<gridDataForm>* gridData)
{
    mData = mainData;
    gData = gridData;
}

FileThread::~FileThread()
{

}


void FileThread::run()
{
    QString result;
    /* ... here is the expensive or blocking operation ... */

    QVector<orderDataForm> oneDayData;
    for(qint32 i = 0;i<fileList.size()-1;++i){
        QFile file(directory.filePath(fileList[i]));

        if(i % 5 == 0){
            oneDayData.clear();
        }

        if(file.open(QIODevice::ReadOnly)){
            qDebug()<<file<<'\n';
            QTextStream stream(&file);
            quint16 lineNum = 0;
            while(true){
                QString line = stream.readLine();
                if(!lineNum){
                    ++lineNum;
                    continue;
                }
                if(line.isEmpty()){
                    break;
                }
                orderDataForm row(line.split(','));
                oneDayData.append(row);
            }
        }
        file.close();
        if(i % 5 == 4){
            mData->append(oneDayData);
        }
        ++fileNum;
    }

    QFile file(directory.filePath(fileList[fileList.size()-1]));
    if(file.open(QIODevice::ReadOnly)){
        qDebug()<<file<<'\n';
        QTextStream stream(&file);
        quint16 lineNum = 0;
        while(true){
            QString line = stream.readLine();
            if(!lineNum){
                ++lineNum;
                continue;
            }
            if(line.isEmpty()){
                break;
            }
            gridDataForm row(line.split(','));
            gData->append(row);
        }
    }
    file.close();
    ++fileNum;
    //qDebug() <<mainData.size()<<mainData[0].size()<<mainData[0][0].size();
    //qDebug() <<gridData.size()<<gridData[0].size();
    emit resultReady(result);
}
