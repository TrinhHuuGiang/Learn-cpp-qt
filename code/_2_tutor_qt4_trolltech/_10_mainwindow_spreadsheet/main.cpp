#include "mainwindow.h"
#include "spreadsheet.h"

#include <QApplication>

#include <QScreen>

#include <QSplashScreen>

#include <QTimer>

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


    // Main loop application (init Qt app)
    QApplication a(argc, argv);




    // Splash screen (paint splash screen first)
    QSplashScreen* splash_scr = new QSplashScreen;

    QPixmap pix(":/images/trolltech_icon/open.png");

    QScreen *screen = QGuiApplication::primaryScreen();
    QSize screenSize = screen->size();

    screenSize *= 2.0 / 3.0;

    pix = pix.scaled(
        screenSize,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );

    splash_scr->setPixmap(pix);

    splash_scr->show();


    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash_scr->showMessage(
        QObject::tr("Setting up the main window..."),
        topRight,
        Qt::red
        );


    // Main window + central window is spreadsheet
    MainWindow w;

    Spreadsheet* spreadsheet = new Spreadsheet; // set must be pointer

    // set ownership, spreadsheet now at central of main window
    w.setCentralWidget(spreadsheet);

    // delay splash screen
    QTimer::singleShot(1000, [&]() {

        // w.show();
        w.showFullScreen();

        splash_scr->finish(&w);

    });


    return a.exec();
}
