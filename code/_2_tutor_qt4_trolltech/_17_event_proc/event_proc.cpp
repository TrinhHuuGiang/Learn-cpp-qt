#include "event_proc.h"
#include "ui_event_proc.h"

Event_Proc::Event_Proc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Event_Proc)
{
    ui->setupUi(this);
}

Event_Proc::~Event_Proc()
{
    delete ui;
}
