#include <QApplication>

#include <QDialog>
#include "ui_gotocelldialog.h"

#include <gotocelldialog.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // case 1: Just set to a Dialog
    // Ui::GoToCellDialog ui;
    // QDialog *dialog = new QDialog;

    // ui.setupUi(dialog);

    // dialog->setFixedHeight(dialog->sizeHint().height());
    // dialog->setFixedWidth(dialog->sizeHint().width());
    // dialog->show();

    // case 2: using derived QDialog class with setup ui
    GoToCellDialog gocell_di;

    gocell_di.show();

    return a.exec();
}
