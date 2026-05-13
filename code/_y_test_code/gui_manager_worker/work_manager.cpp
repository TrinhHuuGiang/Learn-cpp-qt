#include "work_manager.h"
#include "mainwindow.h"

#include <QDebug>

work_Manager::work_Manager(QObject *parent)
    : QObject{parent}
{

}


work_Manager::~work_Manager()
{
    qDebug()<< "work manager end (-_-)";
}

void work_Manager::end_manager()
{
    emit end_ack_from_manager();
    deleteLater();
}
