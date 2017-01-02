//#include "playbacktracker.h"
#include <QFileDialog>
#include <QStandardItem>
#include "contextmenu.h"
#include "ui_maplaya2.h"

ContextMenu::ContextMenu(Ui::MaPlaya2* somePlayerUI, QObject *parent)
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
    do
    {
        nModel->removeRow(opaList.takeLast().row());
    }while(!opaList.isEmpty());
}
