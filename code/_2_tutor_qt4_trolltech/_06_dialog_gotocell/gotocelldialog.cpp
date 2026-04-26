#include "gotocelldialog.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>

GoToCellDialog::GoToCellDialog(QDialog *parent)
    : QDialog{parent},
    ui(new Ui::GoToCellDialog)
{
    ui->setupUi(this);

    // add validator with regular expression for lineEdit
    QRegularExpression regExp("[A-Za-z][1-9][0-9]{0,2}");
    ui->lineEdit->setValidator(new QRegularExpressionValidator(regExp, this));



    // signal slot
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    connect(ui->lineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(on_lineEdit_textChanged()));

    // fix window size
    this->setFixedHeight(this->sizeHint().height());
    this->setFixedWidth(this->sizeHint().width());
}

// destructor
GoToCellDialog::~GoToCellDialog()
{
    delete ui; ui = nullptr;
}

// slot

void GoToCellDialog::on_lineEdit_textChanged()
{
    ui->okButton->setEnabled(ui->lineEdit->hasAcceptableInput());
}
