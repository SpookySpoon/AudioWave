#include <QDateTime>
#include <QDebug>
#include "trackwrapper.h"
#include "ui_maplaya2.h"
#include "bass.h"
#include "playbacktracker.h"
#include "staticfunctions.h"

TrackWrapper::TrackWrapper(const QString& someTrackPath, Ui::MaPlaya2 *someUi, QObject* parent)
    :QObject(parent), trackPath(someTrackPath), ui(someUi)
{
    progressTimerSlider = new QTimer(this);
    progressTimerSeconds = new QTimer(this);
    trackInit(trackPath);
    connect(ui->visualTimeline,SIGNAL(moved(int)),this,SLOT(jumpTo(int)));
    connect(ui->visualTimeline,SIGNAL(browsing(int)),this,SLOT(onBrowsing(int)));
    connect(ui->buttonPlay,SIGNAL(clicked()),this,SLOT(pause()));
    connect(ui->buttonPause,SIGNAL(clicked()),this,SLOT(pause()));
    connect(progressTimerSlider,SIGNAL(timeout()),ui->visualTimeline,SLOT(incrementSlider()));//NEW
    connect(progressTimerSlider,SIGNAL(timeout()),this,SLOT(startProgressTimerSlider()));//NEW
    connect(progressTimerSeconds,SIGNAL(timeout()),this,SLOT(startProgressTimerSeconds()));//NEW
    connect(progressTimerSeconds,SIGNAL(timeout()),this,SLOT(onElapsedSec()));//NEW
    connect(progressTimerSeconds,SIGNAL(timeout()),ui->visualTimeline,SLOT(incrementValue()));//NEW
    connect(this,SIGNAL(trackEnded()),this,SLOT(wrapThisUp()));
    BASS_ChannelSetSync(myStream,BASS_SYNC_END,0,StaticFunctions::LoopSyncProc,this);
}

TrackWrapper::~TrackWrapper()
{
    progressTimerSeconds->stop();//NEW
    progressTimerSlider->stop();//NEW
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
    ui->visualTimeline->setMaximum(trackTime);
    ui->labelTimeTotal->setText(QString("%1")
        .arg(QDateTime::fromTime_t(trackTime).toUTC().toString(StaticFunctions::timeFormat(trackTime))));
    ui->labelTimeElapsed->setText(QString("0:00"));
    play();
}

void TrackWrapper::play()
{
    long posBytes=BASS_ChannelGetPosition(myStream,0);
    int posSecs=BASS_ChannelBytes2Seconds(myStream,posBytes);
    ui->visualTimeline->setValue(posSecs);
    startProgressTimerSeconds();
    startProgressTimerSlider();
    BASS_ChannelPlay(myStream,FALSE);
}

void TrackWrapper::pause()
{
    if(BASS_ChannelIsActive(myStream)==BASS_ACTIVE_PLAYING)
    {
        BASS_ChannelPause(myStream);
        remainintTimeSeconds=progressTimerSeconds->remainingTime();//NEW
        remainingTimeSlider=progressTimerSlider->remainingTime();//NEW
        progressTimerSeconds->stop();//NEW
        progressTimerSlider->stop();//NEW
    }
    else
    {
        play();
    }
}

void TrackWrapper::jumpTo(int position)
{
    browsingTime.clear();
    elapsedSeconds=position;//NEW
    ui->labelTimeElapsed->setText(QString("%1%2")
        .arg(QDateTime::fromTime_t(elapsedSeconds).toUTC().toString(StaticFunctions::timeFormat(elapsedSeconds)))
        .arg(browsingTime));
    long posBytes=BASS_ChannelSeconds2Bytes(myStream,position);
    BASS_ChannelSetPosition(myStream,posBytes,0);
    startProgressTimerSeconds();//NEW
    startProgressTimerSlider();//NEW
}

void TrackWrapper::callTrackEnd()
{
    emit trackEnded();
}

void TrackWrapper::onBrowsing(int timePos)
{
        browsingTime=QString("(%1)")
                .arg(QDateTime::fromTime_t(timePos).toUTC().toString(StaticFunctions::timeFormat(timePos)));
        QString elapsedSec=QString("%1")
                .arg(QDateTime::fromTime_t(elapsedSeconds).toUTC().toString(StaticFunctions::timeFormat(elapsedSeconds)));
        ui->labelTimeElapsed->setText(QString("%1%2")
            .arg(elapsedSec)
            .arg(browsingTime));
}

void TrackWrapper::startProgressTimerSlider()
{
    if(!progressTimerSlider->isActive())
    {
        progressTimerSlider->start(remainingTimeSlider);
        remainingTimeSlider=200;//NEW
    }
    else
    {
        remainingTimeSlider=200;//NEW
        progressTimerSlider->start(remainingTimeSlider);//NEW
    }
}

void TrackWrapper::startProgressTimerSeconds()
{
    if(!progressTimerSeconds->isActive())
    {
        progressTimerSeconds->start(remainintTimeSeconds);
        remainintTimeSeconds=1000;//NEW
    }
    else
    {
        remainintTimeSeconds=1000;//NEW
        progressTimerSeconds->start(remainintTimeSeconds);//NEW
    }
}

void TrackWrapper::onElapsedSec()//NEW
{
    elapsedSeconds++;
    ui->labelTimeElapsed->setText(QString("%1%2")
        .arg(QDateTime::fromTime_t(elapsedSeconds).toUTC().toString(StaticFunctions::timeFormat(elapsedSeconds)))
        .arg(browsingTime));
}

void TrackWrapper::wrapThisUp()
{
    progressTimerSeconds->stop();//NEW
    progressTimerSlider->stop();//NEW
    BASS_Stop();
    BASS_Free();
    emit callNewTrack();
}

