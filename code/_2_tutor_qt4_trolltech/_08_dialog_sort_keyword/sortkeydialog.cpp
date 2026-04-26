#include "sortkeydialog.h"
#include "ui_sortkeydialog.h"

SortKeyDialog::SortKeyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SortKeyDialog)
{
    ui->setupUi(this);
}

SortKeyDialog::~SortKeyDialog()
{
    delete ui;
}
