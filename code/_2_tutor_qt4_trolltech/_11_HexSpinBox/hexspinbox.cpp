#include "hexspinbox.h"
#include "ui_hexspinbox.h"

#include <QRegularExpression>


HexSpinBox::HexSpinBox(QWidget *parent)
    : QSpinBox(parent)
    , ui(new Ui::HexSpinBox)
{
    // ui->setupUi(this);

    setRange(0, 1023);
    validator = new QRegularExpressionValidator(QRegularExpression("[0-9A-Fa-f]{1,8}"), this);
}

HexSpinBox::~HexSpinBox()
{
    // delete ui;
}


QValidator::State HexSpinBox::validate(QString &text, int &pos) const
{
    return validator->validate(text, pos);
}

QString HexSpinBox::textFromValue(int value) const
{
    return QString::number(value, 16).toUpper();
}

int HexSpinBox::valueFromText(const QString &text) const
{
    bool ok;
    return text.toInt(&ok, 16);
}
