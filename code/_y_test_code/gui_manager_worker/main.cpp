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
 * 1. Message dialog when `exec` will block main thread.
 *      - using `show` instead will display as normal widget without blocking
 * 2. After MainWindow w close success, see that main() print:
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
 * 3. Which thread the QThread belong to?
 *      - refer: https://doc.qt.io/qt-6/qthread.html
 *      `
 *      It is important to remember that a QThread instance lives in the
 *      old thread that instantiated it, not in the new thread that calls run().
 *      This means that all of QThread's queued slots and invoked methods will
 *      execute in the old thread. Thus, a developer who wishes to invoke slots
 *      in the new thread must use the worker-object approach; new slots should
 *      not be implemented directly into a subclassed QThread.
 *      `
 *      - So QThread belong to the thread (A) initialized it.
 *      - Signal - slot on >QThread< will executed in thread (A)
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
