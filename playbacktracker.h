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
    ~PlaybackTracker();
private:
    void play(const QString& file, int volume);
    MaPlaya2* newPlayer=nullptr;
    Ui::MaPlaya2 *ui=nullptr;
    QList<TrackWrapper*> tracks;
    QPersistentModelIndex trackPlayed;
    QStandardItemModel* nModel=nullptr;
private slots:
    void playNext();
    void onListViewDoubleClick(QModelIndex trackIndex);
    void onPlaylistShuffle(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
};

