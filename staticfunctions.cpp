#include <QDebug>
#include "trackwrapper.h"
#include "playbacktracker.h"
#include "staticfunctions.h"

StaticFunctions::StaticFunctions()
{

}


QString StaticFunctions::timeFormat(int seconds)
{
    if(seconds>3599)
    {
        return QString("h:m:ss");
    }
    else
    {
        return QString("m:ss");
    }
}

void CALLBACK StaticFunctions::LoopSyncProc(HSYNC handle, DWORD channel, DWORD data, void *user)
{
    TrackWrapper* opaP=reinterpret_cast<TrackWrapper*>(user);
    opaP->callTrackEnd();
//    BASS_ChannelPlay(channel,FALSE);
}
