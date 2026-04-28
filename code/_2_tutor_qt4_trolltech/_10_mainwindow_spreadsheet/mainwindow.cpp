#include "mainwindow.h"
#include "ui_mainwindow.h"

// Qt widget
#include <QMessageBox> // test reject, accept from dialog

#include <QCloseEvent>  // override closeEvent required

// Qt action/menu
// #include <QMenuBar>

// Qt misc
#include <QDebug>

/**
 * ==================================================
 * Main window class
 * ==================================================
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->showMaximized();

    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}


//========== Chunk 1 =========

void MainWindow::closeEvent(QCloseEvent *event)
{

    QMessageBox msg(this);
    msg.setText("Test accept/reject?");
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    QMessageBox::StandardButton ret = (QMessageBox::StandardButton)msg.exec();

    if(ret == QMessageBox::Ok)
    {
        event->accept();
    } else {
        event->ignore();
    }
}


//========== Chunk 2 =========

void MainWindow::newFile(){ qDebug() << "request slot: newFile"; }



//========== Chunk 3 =========
void MainWindow::createActions()
{

    // Action: new
    // Label and parent:
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    // Shortcut
    newAction->setShortcut(tr("Ctrl+N"));
    // Status
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    // Signal: triggered()
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);

    fileMenu->addSeparator();

    fileMenu->addAction(newAction); // check no duplicate when display menu

}


