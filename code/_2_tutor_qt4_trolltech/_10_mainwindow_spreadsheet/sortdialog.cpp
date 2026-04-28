#include "sortdialog.h"
#include "ui_sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SortDialog)
{
    ui->setupUi(this);

    // hide second and thirt groupbox
    ui->secondaryGroupBox->hide();
    ui->tertiaryGroupBox->hide();

    // set layout fixed user can't resize
    // - the dialog still resize when child widget hide/show
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    // this->setFixedHeight(this->sizeHint().height());
    // this->setFixedWidth(this->sizeHint().width());

    setColumnRange('A', 'Z');
}

SortDialog::~SortDialog()
{
    delete ui;
}


void SortDialog::setColumnRange(QChar first, QChar last)
{
    ui->primaryColumnCombo->clear();
    ui->secondaryColumnCombo->clear();
    ui->tertiaryColumnCombo->clear();
    ui->secondaryColumnCombo->addItem(tr("None"));
    ui->tertiaryColumnCombo->addItem(tr("None"));
    ui->primaryColumnCombo->setMinimumSize(
    ui->secondaryColumnCombo->sizeHint());

    QChar ch = first;
    while (ch <= last) {
        ui->primaryColumnCombo->addItem(QString(ch));
        ui->secondaryColumnCombo->addItem(QString(ch));
        ui->tertiaryColumnCombo->addItem(QString(ch));
        ch = QChar(ch.unicode() + 1);
    }
}
