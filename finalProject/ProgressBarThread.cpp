#include "progressBarThread.h"
#include "global.h"


ProgressBarThread::ProgressBarThread(QProgressBar* QPB)
{
    PB = QPB;
}

ProgressBarThread::~ProgressBarThread()
{

}

void ProgressBarThread::run()
{
    while(fileNum <= allFileNum){
        PB->setValue(fileNum);
    }
}
