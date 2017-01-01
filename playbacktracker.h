#pragma once
#include <QModelIndex>
#include <QObject>
class MaPlaya2;

namespace Ui {
class MaPlaya2;
}
class TrackWrapper;
class PlaybackTracker:public QObject
{
    Q_OBJECT
public:
    PlaybackTracker(QObject* parent=nullptr);
private:
    void play(const QString& file, int volume);
    void playNextTrack();
    MaPlaya2* newPlayer=nullptr;
    Ui::MaPlaya2 *ui;
    QStringList pFiles;
    QList<TrackWrapper*> tracks;
private slots:
    void onPlayButton();
    void onPauseButton();
    void onAddFilesButton();
    void onIndexesMoved(QModelIndexList);
    void onListViewDoubleClick(QModelIndex trackIndex);
};

