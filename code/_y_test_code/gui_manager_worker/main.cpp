/*
 * Gui Thread
 * - Gui blocking, filtering
 * - Gui displaying from Manager
 *
 * Manager
 * - Control Gui
 * - Manage worker
 *
 * Worker thread
 * - Do the job follow Manager commands
 *
 *
 * Some note:
 * - Message dialog when `exec` will block main thread.
 *      - using `show` instead will display as normal widget without blocking
 * - After MainWindow w close success, see that main() print:
 *      qDebug() << "main event loop end !";
 *   But `msgbox_closing` of w still displays
 *   That mean `QApplication::exec` do not care the `QMessageBox`
 *
 *   when F1 on `QApplication::exec` Qt point that:
 *      `
 *      Generally, no user interaction can take place before calling exec().
 *      As a special case, modal widgets like QMessageBox can be used before
 *      calling exec(), because modal widgets call exec() to start a local
 *      event loop.
 *      `
 *   => QMessageBox run in itself event loop, independent with main event loop.
 *
 */


#include "mainwindow.h"

#include <QThread>
#include <QObject>

#include <QApplication>

#include <QThread>

#include <QDebug>

int main(int argc, char *argv[])
{
    int ret_exec = 0;

    QApplication a(argc, argv);
    QThread::currentThread()->setObjectName("GUI thread");


    MainWindow w;

    /* ===== Execute =====
     * Any signal slot in main thread will not available after a.exec() return.
     * So before exec,
     */
    w.show();
    ret_exec = a.exec();

    qDebug() << "main event loop end !";
    return ret_exec;
}
