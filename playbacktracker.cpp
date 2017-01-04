#include <QStandardItem>
#include <QDebug>
#include "trackwrapper.h"
#include "contextmenu.h"
#include "playbacktracker.h"
#include "playerui.h"
#include "ui_plauerui.h"
#include "bass.h"

PlaybackTracker::PlaybackTracker(QObject* parent)
    :QObject(parent)
{
    ui = new Ui::PlayerUI;
    newPlayer=new PlayerUI(ui);
    nModel= new QStandardItemModel(this);
    ui->listView->setModel(nModel);
    listViewMenu=new ContextMenu(ui,this);
    newPlayer->show();
    connect(ui->buttonStop,SIGNAL(clicked()),this,SLOT(onButtonStop()));
    connect(ui->listView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onListViewDoubleClick(QModelIndex)));
}

void PlaybackTracker::onListViewDoubleClick(QModelIndex trackIndex)
{
    loadTrack(trackIndex);
    ui->buttonPlay->click();
}
void PlaybackTracker::onButtonStop()
{
    QPersistentModelIndex tmpI=listViewMenu->getTrackToPlay();
    if(tmpI.row()!=-1)
    {
        loadTrack(tmpI);
        ui->visualTimeline->repaint();
    }
    else
    {
        ejectTracks();
    }
}
void PlaybackTracker::loadTrack(QModelIndex trackIndex)
{
    auto buttons = qApp->mouseButtons();
    if(buttons==Qt::RightButton)                //Отсеиваем правые кнопки мыши.
    {return;} 
    ejectTracks();                              //Если вызов производился левой кнопкой, то удаляем созданный канал
    QString fP=trackIndex.data().toString();    //и создаём новый.
    tracks.append(new TrackWrapper(fP, ui, this));
    trackPlayed=trackIndex;
    listViewMenu->setTrackToPlay(trackIndex);
    connect(tracks.last(),SIGNAL(callNewTrack()),this,SLOT(playNext()));
}
void PlaybackTracker::playNext()
{
    listViewMenu->getNextTrack();
    QPersistentModelIndex tmpI=listViewMenu->getTrackToPlay();
    if(tmpI.row()!=-1)
    {
        onListViewDoubleClick(tmpI);
    }
    else
    {
        ejectTracks();
    }
}
void PlaybackTracker::ejectTracks()
{
    if(!tracks.isEmpty())
    {
        delete tracks.last();
        tracks.clear();
    }
    ui->visualTimeline->resetSlider(0);
    ui->labelTimeElapsed->setText("-:--");
    ui->labelTimeTotal->setText("-:--");
    ui->labelSongName->setText("");
}


