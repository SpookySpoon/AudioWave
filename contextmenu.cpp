//#include "playbacktracker.h"
#include <QDebug>
#include <QFileDialog>
#include <QStandardItem>
#include "contextmenu.h"
#include "ui_plauerui.h"

ContextMenu::ContextMenu(Ui::PlayerUI* somePlayerUI, QObject *parent)
    :QObject(parent), playerUI(somePlayerUI)
{
    nModel= qobject_cast<QStandardItemModel*>(playerUI->listView->model());
    QAction *addFiles = new QAction(tr("Add Files"), playerUI->listView);
    QAction *removeFiles = new QAction(tr("Remove Files"), playerUI->listView);
    playerUI->listView->addAction(addFiles);
    playerUI->listView->addAction(removeFiles);
    playerUI->listView->setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(addFiles,SIGNAL(triggered()),this,SLOT(onAddFilesButton()));
    connect(removeFiles,SIGNAL(triggered()),this,SLOT(onRemoveFilesButton()));
    connect(playerUI->listView->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this,SLOT(onPlaylistShuffle(QModelIndex,QModelIndex,QVector<int>)));
}

void ContextMenu::onAddFilesButton()
{
    QFileDialog getFilesDialog;
    getFilesDialog.setNameFilter(tr("*.CDA *.AAC *.AC3 *.APE*.DTS *.FLAC *.IT *.MIDI *.MO3"
                   "*.MOD *.M4A *.M4B *.MP1 *.MP2 *.MP3 *.MPC*.MTM *.OFR *.OGG *.OPUS *.RMI"
                   "*.S3M *.SPX*.TAK *.TTA *.UMX *.WAV *.WMA *.WV *.XM *.DSF *.DFF"));
    getFilesDialog.setFileMode(QFileDialog::ExistingFiles);
    if(getFilesDialog.exec())
    {
        QStringList pFiles=getFilesDialog.selectedFiles();
        for (auto i:pFiles)
        {
            QStandardItem* opaItem=new QStandardItem(i);
            opaItem->setFlags(Qt::ItemIsEnabled|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
            nModel->appendRow(opaItem);
        }
    }
    else {
        return;
    }
}

void ContextMenu::onRemoveFilesButton()
{
    QModelIndexList opaList=playerUI->listView->selectionModel()->selectedIndexes();
    std::sort(opaList.begin(),opaList.end(),qGreater<QModelIndex>());

    for (auto i:opaList)
    {
        if(i==trackToPlay)
        {
            getNextTrack();
            ignoreNextTrack=true;
        }
        emit removing(i.data().toString());
        nModel->removeRow(i.row());
    }
}

void ContextMenu::setTrackToPlay(const QPersistentModelIndex& playedIndex)
{
    trackToPlay=playedIndex;
    ignoreNextTrack=false;
}

QPersistentModelIndex ContextMenu::getTrackToPlay()
{
    return trackToPlay;
}
void ContextMenu::getNextTrack()
{
    if(ignoreNextTrack)
    {return;}
    if(nModel->rowCount()-1>trackToPlay.row())
    {
        setTrackToPlay(nModel->index(trackToPlay.row()+1,0));
    }
    else
    {
        setTrackToPlay(nModel->index(0,0));
    }
}

void ContextMenu::onPlaylistShuffle
(const QModelIndex &topLeft, const QModelIndex &, const QVector<int> &)
{
    if(trackToPlay.data()==topLeft.data())
    {
        trackToPlay=topLeft;
    }
}
