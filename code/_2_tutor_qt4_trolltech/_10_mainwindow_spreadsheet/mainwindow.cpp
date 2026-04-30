#include "mainwindow.h"
#include "ui_mainwindow.h"

// Qt widget
#include <QMessageBox> // test reject, accept from dialog

#include <QCloseEvent>  // override closeEvent required

// Qt action/menu
// #include <QMenuBar>

// Qt misc
#include <QDebug>

#include <QPixmap> // pixel image

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

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();
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
    newAction->setIcon(QIcon(":/images/trolltech_icon/new.png"));
    // Shortcut
    newAction->setShortcut(tr("Ctrl+N"));
    // Status
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    // Signal: triggered()
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));


    // Action: color_red_act
    // Label and parent:
    color_red_act = new QAction(tr("&RED"), this);

    QPixmap pix_red(32,32);
    pix_red.fill(Qt::red);
    color_red_act->setIcon(QIcon(pix_red));

    // Shortcut
    color_red_act->setShortcut(tr("Ctrl+R"));
    // Status
    color_red_act->setStatusTip(tr("This is a RED action"));
    // Signal: triggered()
        // no trigger

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);

    fileMenu->addSeparator();

    // fileMenu->addAction(newAction); // check no duplicate when display menu

    fileMenu->addAction(color_red_act);
}

void MainWindow::createContextMenu()
{
    menuBar()->addAction(newAction);

    menuBar()->addAction(color_red_act);

    menuBar()->setContextMenuPolicy(Qt::ActionsContextMenu);
}


void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(newAction);
    editToolBar->addSeparator();
    // editToolBar->addAction(newAction); // check no duplicate when display

    editToolBar->addAction(color_red_act);

}



void MainWindow::createStatusBar()
{
    locationLabel = new QLabel(" W999 ", this);
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());
    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);
    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);

    // connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)),
    //         this, SLOT(updateStatusBar()));
    // connect(spreadsheet, SIGNAL(modified()),
    //         this, SLOT(spreadsheetModified()));
    // updateStatusBar();
}
