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
    BASS_SetVolume(ui->sliderVolume->value());
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
    loadTrack(listViewMenu->getTrackToPlay());
    ui->visualTimeline->repaint();
}
void PlaybackTracker::loadTrack(QModelIndex trackIndex)
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
    listViewMenu->setTrackToPlay(trackIndex);
    connect(tracks.last(),SIGNAL(callNewTrack()),this,SLOT(playNext()));
}
void PlaybackTracker::playNext()
{
    listViewMenu->getNextTrack();
    onListViewDoubleClick(listViewMenu->getTrackToPlay());
}




