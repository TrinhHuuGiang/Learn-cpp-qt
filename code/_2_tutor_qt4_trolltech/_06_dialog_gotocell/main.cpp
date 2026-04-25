#include <QApplication>

#include <QDialog>
#include "ui_dialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ui::GoToCellDialog ui;
    QDialog *dialog = new QDialog;

    ui.setupUi(dialog);

    dialog->setFixedHeight(dialog->sizeHint().height());
    dialog->show();

    return a.exec();
}
