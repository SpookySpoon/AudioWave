#include "maplaya2.h"
#include "ui_maplaya2.h"

MaPlaya2::MaPlaya2(Ui::MaPlaya2* playerUI, QWidget *parent) :
    QWidget(parent), ui(playerUI)
{
    ui->setupUi(this);
}

MaPlaya2::~MaPlaya2()
{
    delete ui;
}
