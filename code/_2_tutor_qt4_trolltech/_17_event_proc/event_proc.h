#ifndef EVENT_PROC_H
#define EVENT_PROC_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Event_Proc;
}
QT_END_NAMESPACE

class Event_Proc : public QWidget
{
    Q_OBJECT

public:
    Event_Proc(QWidget *parent = nullptr);
    ~Event_Proc();

// event handler
    // bool keyPressEvent(QKeyEvent *event) override;

private:
    Ui::Event_Proc *ui;
};
#endif // EVENT_PROC_H
