#include "hexspinbox.h"
#include "iconeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HexSpinBox w;
    w.show();
    return a.exec();
}
