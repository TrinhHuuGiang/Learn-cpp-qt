#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QWidget>
#include <QSpinBox>

#include <QValidator>
#include <QRegularExpressionValidator>

namespace Ui {
class HexSpinBox;
}

class HexSpinBox : public QSpinBox
{
    Q_OBJECT

public:
// initialization
    explicit HexSpinBox(QWidget *parent = nullptr);
    ~HexSpinBox();


protected:
//
    QValidator::State validate(QString &text, int &pos) const;
    int valueFromText(const QString &text) const;
    QString textFromValue(int value) const;


// variables
private:
    Ui::HexSpinBox *ui;

    QRegularExpressionValidator *validator;

};

#endif // HEXSPINBOX_H
