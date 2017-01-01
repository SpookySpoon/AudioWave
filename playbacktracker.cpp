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
    newPlayer->show();
    connect(ui->buttonPlay,SIGNAL(clicked()),this,SLOT(onPlayButton()));
    connect(ui->buttonAddFiles,SIGNAL(clicked()),this,SLOT(onAddFilesButton()));
    connect(ui->buttonPause,SIGNAL(clicked()),this,SLOT(onPauseButton()));
    connect(ui->listView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onListViewDoubleClick(QModelIndex)));
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
        QStandardItemModel* nModel = new QStandardItemModel(this);
        for (auto i:pFiles)
        {
            QStandardItem* opaItem=new QStandardItem(i);
            opaItem->setFlags(Qt::ItemIsEnabled|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
            nModel->appendRow(opaItem);
        }
        ui->listView->setModel(nModel);
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
}


void PlaybackTracker::onPauseButton()
{
    qDebug()<<ui->listView->model()->index(2,0).data();
//    for (auto i:pFiles)
//    {
//        qDebug()<<i;
//    }
}
void PlaybackTracker::onPlayButton()
{

}

void PlaybackTracker::playNextTrack()
{
//    ui->listView->i
}

void PlaybackTracker::onIndexesMoved(QModelIndexList list)
{
    for (auto i:list)
    {
        qDebug()<<i.data().toString();
    }

}


