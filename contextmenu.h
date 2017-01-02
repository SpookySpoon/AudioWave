#pragma once

#include <QObject>
namespace Ui {
class MaPlaya2;
}
class QStandardItemModel;
class ContextMenu:public QObject
{
    Q_OBJECT
public:
    ContextMenu(Ui::MaPlaya2* playerUI, QObject* parent=nullptr);
    Ui::MaPlaya2* playerUI=nullptr;
    QStandardItemModel* nModel=nullptr;
private slots:
    void onAddFilesButton();
    void onRemoveFilesButton();
};

