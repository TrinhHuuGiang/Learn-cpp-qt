#include "mainwindow.h"
#include "spreadsheet.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Fix missing menubar
        // F1 for more information
        // attribute must set before
        // creating QCoreApplication (or QApplication)
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

        // render by CPU
    // QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);

        // using Open Graphic Library Embedded System
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);

    QApplication a(argc, argv);



    MainWindow w;
    // w.show();
    w.showFullScreen();

    Spreadsheet* spreadsheet = new Spreadsheet; // set must be pointer

    // set ownership, spreadsheet now at central of main window
    w.setCentralWidget(spreadsheet);

    return a.exec();
}
