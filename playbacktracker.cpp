#include <QStandardItem>
#include <QDebug>
#include <QStringListModel>
#include <QFileDialog>
#include "trackwrapper.h"
#include "contextmenu.h"
#include "playbacktracker.h"
#include "maplaya2.h"
#include "ui_maplaya2.h"
#include "bass.h"

PlaybackTracker::PlaybackTracker(QObject* parent)
    :QObject(parent)
{
    ui = new Ui::MaPlaya2;
    newPlayer=new MaPlaya2(ui);
    nModel= new QStandardItemModel(this);
    ui->listView->setModel(nModel);
    ContextMenu* conMenu=new ContextMenu(ui,this);

    newPlayer->show();
    connect(ui->listView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onListViewDoubleClick(QModelIndex)));
    connect(ui->listView->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this,SLOT(onPlaylistShuffle(QModelIndex,QModelIndex,QVector<int>)));
}

PlaybackTracker::~PlaybackTracker()
{

}

void PlaybackTracker::onListViewDoubleClick(QModelIndex trackIndex)
{
    //Отсеиваем правые кнопки мыши.
    auto buttons = qApp->mouseButtons();
    if(buttons==Qt::RightButton)
    {return;}
    //Если вызов производился левой кнопкой, то удаляем созданный канал и создаём новый.
    if(!tracks.isEmpty())
    {
        delete tracks.last();
        tracks.clear();
    }
    QString fP=trackIndex.data().toString();
    tracks.append(new TrackWrapper(fP, ui, this));
    trackPlayed=trackIndex;
    connect(tracks.last(),SIGNAL(callNewTrack()),this,SLOT(playNext()));
}

void PlaybackTracker::playNext()
{
    int currentRow = trackPlayed.row();
    if(nModel->rowCount()-1>currentRow)
    {
        onListViewDoubleClick(nModel->index(currentRow+1,0));
    }
    else
    {

        onListViewDoubleClick(nModel->index(0,0));
    }
}

void PlaybackTracker::onPlaylistShuffle
(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    if(trackPlayed.data()==topLeft.data())
    {
        trackPlayed=topLeft;
    }
}



