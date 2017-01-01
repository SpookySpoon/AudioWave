#ifndef STATICFUNCTIONS_H
#define STATICFUNCTIONS_H
#include <QString>
#include "bass.h"

class StaticFunctions
{
public:
    StaticFunctions();
    static QString timeFormat(int seconds);
    static void CALLBACK LoopSyncProc(HSYNC handle, DWORD channel, DWORD data, void *user);
    static void *fPtr();
};

#endif // STATICFUNCTIONS_H
