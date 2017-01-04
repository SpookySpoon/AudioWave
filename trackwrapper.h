#pragma once
#include <QObject>
#include <QTimer>
#include "bass.h"
namespace Ui {
class PlayerUI;
}

class TrackWrapper:public QObject
{
    Q_OBJECT
public:
    TrackWrapper(const QString& trackPath, Ui::PlayerUI *ui, QObject* parent=nullptr);
    ~TrackWrapper();
private:
    void nullPosition();
    void channelStop();
    QString browsingTime;
    uint myStream=0;
    Ui::PlayerUI *ui=nullptr;
    QTimer* progressTimerSlider=nullptr;
    QTimer* progressTimerSeconds=nullptr;
    int remainintTimeSeconds=1000, remainingTimeSlider=200, elapsedSeconds=0;
private slots:
    void wrapThisUp();
    void trackInit(const QString& file);
    void jumpTo(int);
    void play();
    void onButtonPlay();
    void onButtonPause();
    void onVolumeChange(int volume);
    void onBrowsing(int);
    void startProgressTimerSlider();
    void startProgressTimerSeconds();
    void onElapsedSec();
signals:
    void trackEnded();
    void callNewTrack();
};
