#include "musicprocessworker.h"

MusicProcessWorker::MusicProcessWorker(QObject *parent) : QThread(parent)
{

}


void MusicProcessWorker::run()
{
    while(!_items.empty()){
        if(_bSuspend)break;
    }
}
