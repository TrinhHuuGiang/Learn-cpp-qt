#include "event_proc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Event_Proc w;
    w.show();
    return a.exec();
}
