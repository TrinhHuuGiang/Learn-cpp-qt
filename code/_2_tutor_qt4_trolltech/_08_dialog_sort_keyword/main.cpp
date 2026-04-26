#include "sortkeydialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SortKeyDialog w;
    // w.show();
    w.showMinimized();
    return a.exec();
}
