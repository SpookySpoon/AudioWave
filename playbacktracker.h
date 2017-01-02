#pragma once
#include <QModelIndex>
#include <QObject>
class MaPlaya2;

namespace Ui {
class MaPlaya2;
}
class TrackWrapper;
class QStandardItemModel;
class PlaybackTracker:public QObject
{
    Q_OBJECT
public:
    PlaybackTracker(QObject* parent=nullptr);
private:
    void play(const QString& file, int volume);
    MaPlaya2* newPlayer=nullptr;
    Ui::MaPlaya2 *ui;
    QStringList pFiles;
    QList<TrackWrapper*> tracks;
    QPersistentModelIndex trackPlayed;
    QStandardItemModel* nModel;
private slots:
    void playNext();
    void onPauseButton();
    void onAddFilesButton();
    void onListViewDoubleClick(QModelIndex trackIndex);
    void onPlaylistShuffle(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
};

