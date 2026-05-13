#include "work_manager.h"
#include "mainwindow.h"

#include <QDebug>

#include <QThread>

work_Manager::work_Manager(QObject *parent)
    : QObject{parent}
{

}


work_Manager::~work_Manager()
{
    QThread::sleep(5);

    qDebug()<< "work manager end (-_-), delay 5s";
}

void work_Manager::end_manager()
{
    emit end_ack_from_manager();
    deleteLater();
}
