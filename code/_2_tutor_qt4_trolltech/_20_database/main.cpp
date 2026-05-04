#include "widget.h"

// #include <QApplication>

#include <QtSql/QSqlDatabase>


int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // Widget w;
    // w.show();
    // return a.exec();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    // Note: F1 to addDatabase
    /*
     * Before using the connection, it must be initialized.
     * e.g., call some or all of
     * - setDatabaseName(),
     * - setUserName(),
     * - setPassword(),
     * - setHostName(),
     * - setPort(),
     * - setConnectOptions(),
     * - finally, open().
     */




}
