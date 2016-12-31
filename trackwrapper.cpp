#include <QDateTime>
#include <QDebug>
#include "trackwrapper.h"
#include "ui_maplaya2.h"
#include "bass.h"
#include "staticfunctions.h"

TrackWrapper::TrackWrapper(const QString& someTrackPath, Ui::MaPlaya2 *someUi, QObject* parent)
    :QObject(parent), trackPath(someTrackPath), ui(someUi)
{
    trackInit(trackPath);
//    connect(ui->sliderTimeLine,SIGNAL(sliderMoved(int)),this,SLOT(jumpTo(int)));
}

TrackWrapper::~TrackWrapper()
{
    BASS_Stop();
    BASS_Free();
}

void TrackWrapper::trackInit(const QString& file)
{
    qDebug()<<"TrackWrapper::play";
    int device = -1; // Default Sounddevice
    int freq = 44100; // Sample rate (Hz)
    BASS_Init(device, freq, 0, 0, NULL);
    myStream=BASS_StreamCreateFile(FALSE,file.toLatin1().data(),0,0,0);
    long chLength = BASS_ChannelGetLength(myStream,0);
    trackTime=BASS_ChannelBytes2Seconds(myStream,chLength);
//    ui->sliderTimeLine->setMaximum(trackTime);
    ui->labelTimeTotal->setText(QString("%1")
        .arg(QDateTime::fromTime_t(trackTime).toUTC().toString(StaticFunctions::timeFormat(trackTime))));
    BASS_ChannelPlay(myStream,FALSE);
}

void TrackWrapper::jumpTo(int position)
{
    long posBytes=BASS_ChannelSeconds2Bytes(myStream,position);
    BASS_ChannelSetPosition(myStream,posBytes,0);
}
