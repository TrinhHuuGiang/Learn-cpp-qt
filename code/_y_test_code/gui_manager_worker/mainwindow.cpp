#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QMessageBox>


#include <QThread>
#include "work_manager.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , thread_manager(new QThread)
    , work_manager(new work_Manager)
    , msgbox_closing(new QMessageBox(this))
{
    ui->setupUi(this);

    this->setObjectName("Main Window");

    // set name manager, thread
    thread_manager->setObjectName("manager Thread");
    thread_manager->start();
    work_manager->setObjectName("work Manager");
    work_manager->moveToThread(thread_manager);

    qDebug() << this << "Rename thread: " << thread_manager;
    qDebug() << this << "Rename obj: " << work_manager;

    // signal - slot
    connect(this, SIGNAL(request_end_to_manager()),
            work_manager, SLOT(end_manager()), Qt::QueuedConnection);

        // make sure manager call end_ack_from_manager()
        //   the deleteLater().
        //   the queue seem like that: execute <== end_ack_from_manager(1)| deleteLater(2) |
        // because
        // this mainwindow onManagerFinished() will quit(), queue stop give more event
    connect(work_manager, SIGNAL(end_ack_from_manager()),
            this, SLOT(onManagerFinished()), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;

    // clean thread
    // wait thread end
    thread_manager->quit();
    thread_manager->wait();
    thread_manager->deleteLater();

    //qDebug
    qDebug()<< "MainWindow end (-_-)";
}


void MainWindow::closeEvent(QCloseEvent* event)
{

    if(close_safe)
    {
        event->accept();
    }
    else
    {
        // blocking msg box
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Title - Exit",
            "Question - Do you want to close ?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            // wait manager end
            emit request_end_to_manager();

            // // hide window
            // this->hide();

            // block user interact with window
            this->setEnabled(false);



            // block close window -> because end the main exec
            if(close_safe) event->accept();
            else
            {
                // non blocking message box
                msgbox_closing->setWindowTitle("Shutting down");
                msgbox_closing->setText("Please wait...");
                msgbox_closing->setStandardButtons(QMessageBox::NoButton);
                msgbox_closing->show();

                event->ignore();
            }
        }
        else
        {
            event->ignore();
        }
    }
}


void MainWindow::onManagerFinished()
{
    this->close_safe = true;
    this->close();

    //qDebug
    qDebug()<< "MainWindow onManagerFinished";
}
