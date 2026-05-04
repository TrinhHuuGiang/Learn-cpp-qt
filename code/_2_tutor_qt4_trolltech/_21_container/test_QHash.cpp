#include "main.h"

#include <QHash>

#include <iostream>
#include <string>

void test_QHash()
{
    QHash<std::string ,double> hash;

    qDebug()<< "Init:";
    qDebug()<< "hash size: " << hash.size();

    std::string tmplate[] = {
        "in_first",
        "in_2",
        "in_4",
        "in_6",
        "in_8",
        "in_3",
        "in_5",
        "in_7",
        "in_9",
        "in_last"
    };

    int size_tmplate = sizeof(tmplate)/sizeof(tmplate[0]);


    for(int i = 0 ; i < size_tmplate ; ++i)
    {
        if(hash.contains(tmplate[i]))
            std::cout << "detect insert duplicated key: "
                      << tmplate[i] << std::endl;
        else
            hash.insert(tmplate[i], i);
    }


    std::cout << "Hash after insert -> search by key\n";

    for(int i = 0; i< size_tmplate ; ++ i)
    {
        if(hash.contains(tmplate[i]))
            std::cout << "k[ v[" << tmplate[i] << "] v["
                      << hash.value(tmplate[i]) << "]" << std::endl;
        else
            std::cout << "k[ v[" << tmplate[i] << "] no value"
                      << std::endl;
    }

    std::cout.flush();
}
