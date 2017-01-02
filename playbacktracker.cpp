#include <QStandardItem>
#include <QDebug>
#include <QStringListModel>
#include <QFileDialog>
#include "trackwrapper.h"
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
    newPlayer->show();
    connect(ui->buttonAddFiles,SIGNAL(clicked()),this,SLOT(onAddFilesButton()));
    connect(ui->buttonPause,SIGNAL(clicked()),this,SLOT(onPauseButton()));
    connect(ui->listView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onListViewDoubleClick(QModelIndex)));
    connect(ui->listView->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this,SLOT(onPlaylistShuffle(QModelIndex,QModelIndex,QVector<int>)));
}

void PlaybackTracker::onAddFilesButton()
{
    QFileDialog getFilesDialog;
    getFilesDialog.setNameFilter(tr("*.CDA *.AAC *.AC3 *.APE*.DTS *.FLAC *.IT *.MIDI *.MO3"
                   "*.MOD *.M4A *.M4B *.MP1 *.MP2 *.MP3 *.MPC*.MTM *.OFR *.OGG *.OPUS *.RMI"
                   "*.S3M *.SPX*.TAK *.TTA *.UMX *.WAV *.WMA *.WV *.XM *.DSF *.DFF"));
    getFilesDialog.setFileMode(QFileDialog::ExistingFiles);
    if(getFilesDialog.exec())
    {
        pFiles=getFilesDialog.selectedFiles();
        for (auto i:pFiles)
        {
            QStandardItem* opaItem=new QStandardItem(i);
            opaItem->setFlags(Qt::ItemIsEnabled|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
            nModel->appendRow(opaItem);
        }
        trackPlayed=nModel->index(2,0);
    }
    else {
        return;
    }
}
void PlaybackTracker::onListViewDoubleClick(QModelIndex trackIndex)
{
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


void PlaybackTracker::onPauseButton()
{
//    qDebug()<<ui->listView->model()->index(2,0).data();
    qDebug()<<trackPlayed.data().toString()<<"\n"<<trackPlayed.row();
//    for (auto i:pFiles)
//    {
//        qDebug()<<i;
//    }
}

void PlaybackTracker::playNext()
{
    int currentRow = trackPlayed.row();
    if(nModel->rowCount()>currentRow)
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



