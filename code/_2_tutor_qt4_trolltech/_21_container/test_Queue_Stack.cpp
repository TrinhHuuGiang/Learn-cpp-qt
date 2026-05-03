#include "main.h"

// qt
#include <QQueue>
#include <QStack>

// c
#include <iostream>

// cpp
#include <string>

void test_QQ_QS()
{
    QQueue<std::string> queue;
    QStack<std::string> stack;

    qDebug()<< "Init:";
    qDebug()<< "queue size: " << queue.size() <<
        "| stack size: " << stack.size();

    std::string tmplate[] = {
        "in_first",
        "in_2",
        "in_3",
        "in_4",
        "in_5",
        "in_6",
        "in_7",
        "in_8",
        "in_9",
        "in_last"
    };

    int size_tmplate = sizeof(tmplate)/sizeof(tmplate[0]);

    for(int i = 0 ; i < size_tmplate; ++i)
    {
        queue.enqueue(tmplate[i]);
        stack.push(tmplate[i]);
    }



    qDebug()<<"Dequeue -> Queue Elems:";
    int queue_size = queue.size();
    for(int i = 0 ; i < queue_size ; i ++)
    {
        std::cout << "[" << i << "] ";
        if(queue.size()) std::cout << queue.dequeue() << std::endl;
    }

    qDebug()<<"Pop -> Stack Elems:";
    int stack_size = stack.size();
    for(int i = 0 ; i < stack_size ; i ++)
    {
        std::cout << "[" << i << "] ";
        if(stack.size()) std::cout << stack.pop() << std::endl;
    }

    std::cout.flush();

}
