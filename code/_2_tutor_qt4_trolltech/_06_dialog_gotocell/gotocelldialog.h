#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>

#include "ui_gotocelldialog.h"

class GoToCellDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GoToCellDialog(QDialog *parent = nullptr);
    ~GoToCellDialog();

private slots:
    void on_lineEdit_textChanged();

private:
    Ui::GoToCellDialog *ui;

signals:
};

#endif // GOTOCELLDIALOG_H
