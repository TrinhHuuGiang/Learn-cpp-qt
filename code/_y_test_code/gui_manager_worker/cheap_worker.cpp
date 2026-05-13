#include "cheap_worker.h"

#include <QDebug>
#include <QThread>

cheap_Worker::cheap_Worker(QObject *parent)
    : QObject{parent}
{}


cheap_Worker::~cheap_Worker()
{
    QThread::sleep(1);
    qDebug()<< "Deleted worker" << this << "end (-_-), delay 1s";
}


void cheap_Worker::end_worker()
{
    emit end_ack_from_worker();
    deleteLater();
}
