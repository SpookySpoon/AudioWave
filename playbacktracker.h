#pragma once
#include <QModelIndex>
#include <QObject>
class PlayerUI;

namespace Ui {
class PlayerUI;
}
class TrackWrapper;
class QStandardItemModel;
class ContextMenu;
class PlaybackTracker:public QObject
{
    Q_OBJECT
public:
    PlaybackTracker(QObject* parent=nullptr);
private:
    void loadTrack(QModelIndex trackIndex);
    void play(const QString& file, int volume);
    PlayerUI* newPlayer=nullptr;
    Ui::PlayerUI *ui=nullptr;
    QList<TrackWrapper*> tracks;
    QPersistentModelIndex trackPlayed;
    QStandardItemModel* nModel=nullptr;
    ContextMenu* listViewMenu;
private slots:
    void playNext();
    void onButtonStop();
    void onListViewDoubleClick(QModelIndex trackIndex);
};

