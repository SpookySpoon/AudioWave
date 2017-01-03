#include "playerui.h"
#include "ui_plauerui.h"

PlayerUI::PlayerUI(Ui::PlayerUI* playerUI, QWidget *parent) :
    QWidget(parent), ui(playerUI)
{
    ui->setupUi(this);
}

PlayerUI::~PlayerUI()
{
    delete ui;
}
