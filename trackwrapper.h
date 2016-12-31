#pragma once
#include <QObject>

namespace Ui {
class MaPlaya2;
}

class TrackWrapper:public QObject
{
    Q_OBJECT
public:
    TrackWrapper(const QString& trackPath, Ui::MaPlaya2 *ui, QObject* parent=nullptr);
    ~TrackWrapper();
private:
    QString trackPath;
    uint myStream=0;
    int trackTime=0;
    Ui::MaPlaya2 *ui;
private slots:
    void trackInit(const QString& file);
    void jumpTo(int);
};
