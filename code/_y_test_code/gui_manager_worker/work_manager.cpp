#include "work_manager.h"
#include "mainwindow.h"

#include <QDebug>

#include <QThread>

#include "cheap_worker.h"

work_Manager::work_Manager(QObject *parent)
    : QObject{parent}
    , thread_worker(new QThread)
    , worker_1(new cheap_Worker)
    , worker_2(new cheap_Worker)
    , worker_3(new cheap_Worker)
{

    // set name worker, thread
    thread_worker->setObjectName("worker Thread");
    thread_worker->start();


    worker_1->setObjectName("worker 1");
    worker_2->setObjectName("worker 2");
    worker_3->setObjectName("worker 3");

    worker_1->moveToThread(thread_worker);  total_worker_running ++;
    worker_2->moveToThread(thread_worker);  total_worker_running ++;
    worker_3->moveToThread(thread_worker);  total_worker_running ++;


    qDebug() << this << "Rename thread: " << thread_worker;
    qDebug() << this << "Rename obj: \n"
        << worker_1 <<"\n"
        << worker_2 <<"\n"
        << worker_3;


    // signal - slot
    connect(this, SIGNAL(request_end_to_workers()),
            worker_1, SLOT(end_worker()), Qt::QueuedConnection);
    connect(this, SIGNAL(request_end_to_workers()),
            worker_2, SLOT(end_worker()), Qt::QueuedConnection);
    connect(this, SIGNAL(request_end_to_workers()),
            worker_3, SLOT(end_worker()), Qt::QueuedConnection);

    connect(worker_1, SIGNAL(end_ack_from_worker()),
            this, SLOT(on_workers_finished()), Qt::QueuedConnection);
    connect(worker_2, SIGNAL(end_ack_from_worker()),
            this, SLOT(on_workers_finished()), Qt::QueuedConnection);
    connect(worker_3, SIGNAL(end_ack_from_worker()),
            this, SLOT(on_workers_finished()), Qt::QueuedConnection);





    connect(timer, SIGNAL(timeout()),
            this, SLOT(onTimeout()));

    timer->start(16);

}


work_Manager::~work_Manager()
{
    QThread::sleep(1);

    thread_worker->quit();
    thread_worker->wait();
    delete thread_worker;

    qDebug()<< "work manager end (-_-), delay 1";
}

void work_Manager::end_manager()
{
    emit request_end_to_workers();
}


void work_Manager::on_workers_finished()
{
    total_worker_running --;

    qDebug()<< "worker running: "<<total_worker_running;

    if(total_worker_running == 0)
    {
        // now safe to end
        emit end_ack_from_manager();
        deleteLater();
    }
}



void work_Manager::onTimeout()
{
    emit tick();
}
