#include "main.h"

#include <QVector>

#include <cstdio>

void test_QVector()
{
    QVector<double> vect_1(3), vect_2;

    qDebug()<< "Init:";
    qDebug()<< "vect_1 size/cap:" << vect_1.size() << "/" << vect_1.capacity() <<
        "| vect_2 size/cap:" << vect_2.size() << "/" << vect_2.capacity();

    for(int i = 0 ; i < 20 ; ++i)
    {
        vect_1.append(1.1*i);
        vect_2.append(1.2*i);
        qDebug()<< "vect_1 size/cap:" << vect_1.size() << "/" << vect_1.capacity() <<
            "| vect_2 size/cap:" << vect_2.size() << "/" << vect_2.capacity();    
    }

    qDebug()<<"Elems vect_1:";
    for(int i = 0 ; i < vect_1.size() ; i ++)
    {
        std::fprintf(stdout,"[%d] %.3f\n", i, vect_1[i]);
    }

    std::fflush(stdout); // default in C printf is stdout
    // std::fflush(stderr); // but here we test, it is stderr
}
