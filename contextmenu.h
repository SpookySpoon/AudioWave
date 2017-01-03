#pragma once
#include <QModelIndex>
#include <QObject>
namespace Ui {
class PlayerUI;
}
class QStandardItemModel;
class ContextMenu:public QObject
{
    Q_OBJECT
public:
    ContextMenu(Ui::PlayerUI* playerUI, QObject* parent=nullptr);
    void setTrackToPlay(const QPersistentModelIndex& playedIndex);
    QPersistentModelIndex getTrackToPlay();
    void getNextTrack();
private:
    bool ignoreNextTrack=false;
    Ui::PlayerUI* playerUI=nullptr;
    QStandardItemModel* nModel=nullptr;
    QPersistentModelIndex trackToPlay;
private slots:
    void onAddFilesButton();
    void onRemoveFilesButton();
    void onPlaylistShuffle(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
signals:
    void removing(const QString);
};

