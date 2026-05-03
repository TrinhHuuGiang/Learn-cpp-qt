#include "hexspinbox.h"
#include "iconeditor.h"

#include <QApplication>

#include <QImage>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HexSpinBox w;
    w.show();


    IconEditor w2;
    w2.show();

    w2.setIconImage(QImage(":/images/iconeditor.png"));

    return a.exec();
}
