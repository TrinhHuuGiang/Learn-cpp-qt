#ifndef CHEAP_WORKER_H
#define CHEAP_WORKER_H

#include <QObject>

class cheap_Worker : public QObject
{
    Q_OBJECT
public:
    explicit cheap_Worker(QObject *parent = nullptr);
    ~cheap_Worker();

signals:
    void end_ack_from_worker();


private slots:
    void end_worker();

};

#endif // CHEAP_WORKER_H
