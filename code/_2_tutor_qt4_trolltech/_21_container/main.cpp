// #include <QApplication>

#include "main.h"

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    // Widget w;
    // w.show();
    return a.exec();*/

    // Qvector test
    qDebug()<< "---------------QVector";
    test_QVector();

    // QQueue QStack test
    qDebug()<< "---------------QQueue and QStack";
    test_QQ_QS();

    // QMap
    qDebug()<< "---------------QMap";
    test_QMap();

    // QHash
    qDebug()<< "---------------QHash";
    test_QHash();

}
