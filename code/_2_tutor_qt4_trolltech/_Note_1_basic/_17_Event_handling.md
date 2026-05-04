
## Content
- [Event and signal](#1-event-is-using-inside-a-widget)
- [event() and it stream Events](#2-the-event)
- [eventFilter](#event-filter)

---

## Event different from signal
### 1. Event is using inside a widget.

When Qt application start by **exec** an **QApplication** or **QCoreApplication**, 
any time a user interaction with application window will raise an event.

**QApplicatoin** catch this event, check which **Widget** own it then
call **QObject::event()** on that **Widget**.

**Signal** is not *event*, it using with **Slot** to connect
outside the **Widget** to others **Widget**

---

### 2. The **event()**
```cpp
    bool QWidget::event(QEvent *event)
    {
        ...
        return true;    // block sent to parent
        ...
        return false;   // pass to parent
    }
```
- If return **false** that means current **QWidget** don't want or not completely handles this event type,
then **QApplication** will send it to their **parent Widget**.
- If return **true** event marks as ended.


We can override **event()** of **Widget** but it sometime not recommended.
Instead of that, using some **stream event**:
- void **keyPressEvent(QKeyEvent `*event`)**: when press any key on keyboard
- void **paintEvent(QPaintEvent `*event`**): when show Widget, or resize, or request repaint
- void **showEvent(QShowEvent `*event`)**
- void **hideEvent(QHideEvent `*event`)**
- void **closeEvent(QCloseEvent `*event`)**

other common events:
- void keyReleaseEvent(...)
- void mouseReleaseEvent(...)
- void mouseMoveEvent(...)
- void touchEvent(...)
- void moveEvent(...)
- void resizeEvent(...)
- void closeEvent(...)
- void focusInEvent(...)
- void focusOutEvent(...)
- ...

---

## Event filter

When we want to catch **event** before it send to **destination widget**.  
Solution is using method **eventFilter**.

1. One or more child **QObject** will using **installEventFilter(parent_or_specified_filter_qobject)**.
2. When a event raise to one of these children, **eventFilter** of parent will raise first.
    ```cpp
        bool parent::eventFilter(QObject *child_target, QEvent *event)
        {
            ... // handle by child_target

            return true;    // block sent event to child target
            return falsel   // pass it to child target
        }
    ```