#include <QDebug>
#include <QApplication>
#include "playbacktracker.h"
#include <windows.h>
#include <apiset.h>
#include <apisetcconv.h>
#include <minwindef.h>
#include <minwinbase.h>
#include <winbase.h>
#include <winnt.h>
#include <stdio.h>
#include <process.h>
#include <shlobj.h>
#include "bass.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlaybackTracker pbtr;


    return a.exec();
}

