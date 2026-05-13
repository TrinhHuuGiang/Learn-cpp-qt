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
    MainWindow w;



    /* ===== Make thread ===== */
    QThread::currentThread()->setObjectName("GUI thread");

    // QThread* worker_thread_1 = new QThread;
    // QThread* worker_thread_2 = new QThread;
    // QThread* worker_thread_3 = new QThread;
    // worker_thread_1->setObjectName("Worker thread 1");
    // worker_thread_2->setObjectName("Worker thread 2");
    // worker_thread_3->setObjectName("Worker thread 3");

    qDebug() << "Rename thread: " << QThread::currentThread() ;
    // qDebug() << "Rename thread: " << worker_thread_1 ;
    // qDebug() << "Rename thread: " << worker_thread_2 ;
    // qDebug() << "Rename thread: " << worker_thread_3 ;


    /* ===== Make object ===== */

    // QObject* worker_1 = new QObject; worker_1->setObjectName("Worker 1");
    // QObject* worker_2 = new QObject; worker_2->setObjectName("Worker 2");
    // QObject* worker_3 = new QObject; worker_3->setObjectName("Worker 3");

    // qDebug() << "Rename obj: " << worker_1 ;
    // qDebug() << "Rename obj: " << worker_2 ;
    // qDebug() << "Rename obj: " << worker_3 ;

    /* ===== Run thread =====
     * - Call QThread::start
     *      - QThread begin protected run(), the thread will auto starts event loop with itself exec()
     */
    // worker_thread_1->start(); worker_thread_2->start(); worker_thread_3->start();
    // qDebug() << "Run the threads:\n" <<
    //     worker_thread_1 << "\n" << worker_thread_2 << "\n" << worker_thread_3 << "\n";


    /* ===== move Object to right thread =====*/
    // worker_1->moveToThread(worker_thread_1);
    // worker_2->moveToThread(worker_thread_2);
    // worker_3->moveToThread(worker_thread_3);


    /* ===== Connect signal - slot =====
     * - in mainwindow.h, i override close event to ask user close by dialog
     */
    // QObject::connect());

    /* ===== Execute =====
     * Any signal slot in main thread will not available after a.exec() return.
     * So before exec,
     */
    w.show();
    ret_exec = a.exec();

    qDebug() << "main event loop end !";

    /* ===== Stop Thread =====
     * - After QThread::quit(), it tells the thead event loop to exit
     *      - So, what will happen to the remaining events in the event loop?
     *          - in QEventLoop (F1), the QEventLoop::exit(int) do not point
     *              that will handle remain event inqueue, only tell event loop
     *              exit with a return code to the exec()
     *          - on Stack Over Flow: https://stackoverflow.com/questions/50179666/stop-processing-event-queue-immediately-on-qthread-exit
     *              they tell that:
     *                  `QEventLoop always calls processEvents before checking
     *                  whether it should exit. This means that the event-queue
     *                  will always be empty when exec() returns.`
     *          - about QEventLoop::processEvents (F1)
     *      - The suggest is make sure exactly call `deleteLater` on QObject
     *          before  QThread::quit()
     */

    /* ===== Before quit =====
     * Make sure all manager, work were in deleteLater
     */
    // worker_thread_1->quit();
    // worker_thread_2->quit();
    // worker_thread_3->quit();

    // worker_thread_1->wait();
    // worker_thread_2->wait();
    // worker_thread_3->wait();


    /* ===== Clean =====*/

    /* ===== End =====*/


    // delay
    return ret_exec;
}
