#include <QDateTime>
#include <QDebug>
#include "trackwrapper.h"
#include "ui_plauerui.h"
#include "bass.h"
#include "playbacktracker.h"
#include "staticfunctions.h"

TrackWrapper::TrackWrapper(const QString& someTrackPath, Ui::PlayerUI *someUi, QObject* parent)
    :QObject(parent), ui(someUi)
{
    progressTimerSlider = new QTimer(this);
    progressTimerSeconds = new QTimer(this);
    trackInit(someTrackPath);
    connect(ui->visualTimeline,SIGNAL(valueChanged(int)),this,SLOT(jumpTo(int)));
    connect(ui->visualTimeline,SIGNAL(sliderMoved(int)),this,SLOT(onBrowsing(int)));

    connect(ui->buttonPlay,SIGNAL(clicked()),this,SLOT(onButtonPlay()));
    connect(ui->buttonPause,SIGNAL(clicked()),this,SLOT(onButtonPause()));
    connect(ui->sliderVolume,SIGNAL(sliderMoved(int)),this,SLOT(onVolumeChange(int)));

    connect(progressTimerSlider,SIGNAL(timeout()),ui->visualTimeline,SLOT(incrementSlider()));
    connect(progressTimerSlider,SIGNAL(timeout()),this,SLOT(startProgressTimerSlider()));

    connect(progressTimerSeconds,SIGNAL(timeout()),this,SLOT(startProgressTimerSeconds()));
    connect(progressTimerSeconds,SIGNAL(timeout()),this,SLOT(onElapsedSec()));

    connect(this,SIGNAL(trackEnded()),this,SLOT(wrapThisUp()));

    BASS_ChannelSetSync(myStream,BASS_SYNC_END,0,StaticFunctions::LoopSyncProc,this);
}

TrackWrapper::~TrackWrapper()
{
    channelStop();
}

void TrackWrapper::trackInit(const QString& file)
{
    int device = -1; // Default Sounddevice
    int freq = 44100; // Sample rate (Hz)
    BASS_Init(device, freq, 0, 0, NULL);
    myStream=BASS_StreamCreateFile(FALSE,file.toLatin1().data(),0,0,0);
    long chLength = BASS_ChannelGetLength(myStream,0);
    int trackTime=BASS_ChannelBytes2Seconds(myStream,chLength);
    ui->visualTimeline->resetSlider(trackTime);
    ui->labelTimeTotal->setText(StaticFunctions::timeFormat(trackTime));
    ui->labelTimeElapsed->setText(QString("0:00"));
    ui->labelSongName->setText(file);
    BASS_ChannelSlideAttribute(myStream, BASS_ATTRIB_VOL, ui->sliderVolume->value()/(float)100, 20);
}

void TrackWrapper::onButtonPlay()
{
    if(BASS_ChannelIsActive(myStream)==BASS_ACTIVE_PLAYING)
    {
        nullPosition();
    }
    else
    {
        play();
    }
}

void TrackWrapper::nullPosition()
{
    BASS_ChannelSetPosition(myStream,0,0);
    elapsedSeconds=0;
    ui->labelTimeElapsed->setText(QString("0:00"));
    ui->visualTimeline->resetSlider(ui->visualTimeline->maximum());
}

void TrackWrapper::play()
{
    startProgressTimerSeconds();
    startProgressTimerSlider();
    BASS_ChannelPlay(myStream,FALSE);
}

void TrackWrapper::onButtonPause()
{
    if(BASS_ChannelIsActive(myStream)==BASS_ACTIVE_PLAYING)
    {
        BASS_ChannelPause(myStream);
        remainintTimeSeconds=progressTimerSeconds->remainingTime();
        remainingTimeSlider=progressTimerSlider->remainingTime();
        progressTimerSeconds->stop();
        progressTimerSlider->stop();
    }
    else
    {
        play();
    }
}

void TrackWrapper::jumpTo(int position)
{
    browsingTime.clear();
    elapsedSeconds=position;
    ui->labelTimeElapsed->setText(StaticFunctions::timeFormat(elapsedSeconds));
    long posBytes=BASS_ChannelSeconds2Bytes(myStream,position);
    BASS_ChannelSetPosition(myStream,posBytes,0);
    startProgressTimerSeconds();
    startProgressTimerSlider();
}

void TrackWrapper::onBrowsing(int timePos)
{
        browsingTime=QString("(%1)").arg(StaticFunctions::timeFormat(timePos));
        QString elapsedSec=StaticFunctions::timeFormat(elapsedSeconds);
        ui->labelTimeElapsed->setText(QString("%1%2")
            .arg(elapsedSec)
            .arg(browsingTime));
}

void TrackWrapper::startProgressTimerSlider()
{
    if(!progressTimerSlider->isActive())
    {
        progressTimerSlider->start(remainingTimeSlider);
        remainingTimeSlider=200;
    }
    else
    {
        remainingTimeSlider=200;
        progressTimerSlider->start(remainingTimeSlider);
    }
}

void TrackWrapper::startProgressTimerSeconds()
{
    if(!progressTimerSeconds->isActive())
    {
        progressTimerSeconds->start(remainintTimeSeconds);
        remainintTimeSeconds=1000;
    }
    else
    {
        remainintTimeSeconds=1000;
        progressTimerSeconds->start(remainintTimeSeconds);
    }
}

void TrackWrapper::onElapsedSec()
{
    elapsedSeconds++;
    ui->labelTimeElapsed->setText(QString("%1%2")
        .arg(StaticFunctions::timeFormat(elapsedSeconds))
        .arg(browsingTime));
}

void TrackWrapper::onVolumeChange(int volume)
{
    BASS_ChannelSlideAttribute(myStream, BASS_ATTRIB_VOL, volume/(float)100, 20);
}

void TrackWrapper::wrapThisUp()
{
    channelStop();
    emit callNewTrack();
}

void TrackWrapper::channelStop()
{
    progressTimerSeconds->stop();
    progressTimerSlider->stop();
    BASS_Stop();
    BASS_Free();
}


