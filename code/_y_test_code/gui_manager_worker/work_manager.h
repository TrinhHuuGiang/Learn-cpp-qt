#ifndef WORK_MANAGER_H
#define WORK_MANAGER_H

#include <QObject>

class cheap_Worker;
class QThread;
#include <QTimer>

class work_Manager : public QObject
{
    Q_OBJECT
public:
    explicit work_Manager(QObject *parent = nullptr);
    ~work_Manager();

signals:
    void end_ack_from_manager();
private slots:
    void end_manager();


signals:
    void request_end_to_workers();
private slots:
    void on_workers_finished();


signals:
    void tick();
private slots:
    void onTimeout();



private:
    QThread* thread_worker;

    cheap_Worker* worker_1;
    cheap_Worker* worker_2;
    cheap_Worker* worker_3;

    int total_worker_running = 0;


    QTimer *timer = new QTimer(this);
};

#endif // WORK_MANAGER_H
