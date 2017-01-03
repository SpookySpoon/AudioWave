#pragma once

#include <QWidget>

namespace Ui {
class PlayerUI;
}

class PlayerUI : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerUI(Ui::PlayerUI* player, QWidget *parent = 0);
    ~PlayerUI();

private:
    Ui::PlayerUI *ui;
};

