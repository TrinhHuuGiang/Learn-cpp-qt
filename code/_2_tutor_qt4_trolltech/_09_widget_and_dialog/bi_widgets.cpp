#include "bi_widgets.h"
#include "ui_bi_widgets.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);


    // Test button widget
    ui->pushButton->setIcon(QIcon("./camera.svg"));
    ui->toolButton->setIcon(QIcon("./camera.svg"));
    ui->toolButton->setPopupMode(QToolButton::MenuButtonPopup);

    // Test container
    ui->frame_2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
}

Dialog::~Dialog()
{
    delete ui;
}
