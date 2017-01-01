#pragma once
#include <QObject>
#include <QTimer>
#include "bass.h"
namespace Ui {
class MaPlaya2;
}

class TrackWrapper:public QObject
{
    Q_OBJECT
public:
    TrackWrapper(const QString& trackPath, Ui::MaPlaya2 *ui, QObject* parent=nullptr);
    ~TrackWrapper();
    void callTrackEnd();
private:
    QString trackPath;
    QString browsingTime;
    uint myStream=0;
    int trackTime=0;
    int elapsedSeconds=0; //NEW
    Ui::MaPlaya2 *ui;
    QTimer* progressTimerSlider=nullptr;//NEW
    QTimer* progressTimerSeconds=nullptr;//NEW
    int remainintTimeSeconds=1000, remainingTimeSlider=200;//NEW

private slots:
    void trackInit(const QString& file);
    void jumpTo(int);
    void play();
    void pause();
    void onBrowsing(int);
    void startProgressTimerSlider();//NEW
    void startProgressTimerSeconds();//NEW
    void onElapsedSec();//NEW

signals:
    void trackEnded();//NEW
};
