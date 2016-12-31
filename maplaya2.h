#pragma once

#include <QWidget>

namespace Ui {
class MaPlaya2;
}

class MaPlaya2 : public QWidget
{
    Q_OBJECT

public:
    explicit MaPlaya2(Ui::MaPlaya2* player, QWidget *parent = 0);
    ~MaPlaya2();

private:
    Ui::MaPlaya2 *ui;
};

