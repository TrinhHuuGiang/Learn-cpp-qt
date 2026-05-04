// #include <QApplication>

#include <QImage>
#include <QMap>

#include <QFile>
#include <QDataStream>

#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // Dialog w;
    // w.show();
    // return a.exec();


    // Write stream
    {
        QImage image("philip.png");

        // VERIFY 1: kiểm tra ảnh load được hay không
        if (image.isNull()) {
            cerr << "[WRITE] Image load FAILED (isNull = true)\n";
        } else {
            cerr << "[WRITE] Image loaded OK: "
                 << image.width() << "x" << image.height() << endl;
        }

        QMap<QString, QColor> map;
        map.insert("red", Qt::red);
        map.insert("green", Qt::green);
        map.insert("blue", Qt::blue);

        QFile file("facts.dat");
        if (!file.open(QIODevice::WriteOnly)) {
            cerr << "Cannot open file for writing: "
                 << qPrintable(file.errorString()) << endl;
            return 1;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_1);

        out << quint32(0x12345678) << image << map;

        cerr << "[WRITE] Done writing stream\n";
    }




    {
        quint32 n;
        QImage image;
        QMap<QString, QColor> map;

        QFile file("facts.dat");
        if (!file.open(QIODevice::ReadOnly)) {
            cerr << "Cannot open file for reading: "
                 << qPrintable(file.errorString()) << endl;
            return 2;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_1);

        in >> n >> image >> map;

        // VERIFY 1: magic number
        cerr << "[READ] magic number: 0x"
             << hex << n << dec << endl;

        if (n != 0x12345678) {
            cerr << "[READ] WARNING: corrupted or wrong format!\n";
        }

        // VERIFY 2: image
        if (image.isNull()) {
            cerr << "[READ] Image is NULL (failed to deserialize or empty)\n";
        } else {
            cerr << "[READ] Image OK: "
                 << image.width() << "x" << image.height() << endl;
        }

        // VERIFY 3: map content
        cerr << "[READ] Map size: " << map.size() << endl;

        for (auto it = map.begin(); it != map.end(); ++it) {
            cerr << "  key=" << it.key().toStdString()
            << " ("
            << it.value().red() << ","
            << it.value().green() << ","
            << it.value().blue()
            << ")\n";
        }

        cerr << "[READ] Done reading stream\n";
    }

    return 0;
}
