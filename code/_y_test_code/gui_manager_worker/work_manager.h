#ifndef WORK_MANAGER_H
#define WORK_MANAGER_H

#include <QObject>

class work_Manager : public QObject
{
    Q_OBJECT
public:
    explicit work_Manager(QObject *parent = nullptr);
    ~work_Manager();

signals:
    void end_ack_from_manager();

    // request_end_to_workers();


private slots:
    void end_manager();

};

#endif // WORK_MANAGER_H
