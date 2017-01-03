#include <QDebug>
#include <QDateTime>
#include "trackwrapper.h"
#include "playbacktracker.h"
#include "staticfunctions.h"

StaticFunctions::StaticFunctions()
{

}


QString StaticFunctions::timeFormat(int seconds)
{
    QString stringFormat;
    if(seconds>3599)
    {
        stringFormat= QString("h:m:ss");
    }
    else
    {
        stringFormat= QString("m:ss");
    }
    return QString("%1").arg(QDateTime::fromTime_t(seconds).toUTC().toString(stringFormat));
}

void CALLBACK StaticFunctions::LoopSyncProc(HSYNC , DWORD , DWORD , void *user)
{
    TrackWrapper* opaP=reinterpret_cast<TrackWrapper*>(user);
    opaP->trackEnded();
}
