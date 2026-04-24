## Content
- [Make connection with user actions](#make-connection)

## What news:
- management object:
    - QApplication: slot quit()
- widget:
    - QPushButton: signal clicked()
- Connection:
    - QObject: method connect(), macros SIGNAL() and SLOT()

## Make connection
```cpp
001 #include <QApplication>
002 #include <QPushButton>
003 int main(int argc, char *argv[])
004 {
005 QApplication app(argc, argv);
006 QPushButton *button = new QPushButton("Quit");
007 QObject::connect(button, SIGNAL(clicked()),
008 &app, SLOT(quit()));
009 button->show();
010 return app.exec();
011 }
```

---

Line **005**
- The QApplication `app` with designed slot `quit()`
    - Run after called `exec()` method
    - will stop and return after emitted a signel to `quit()` slot

---

Line **006**: 
- `QPushButton` widget can emits a signal `clicked()` when user click on displaying button.

---

Line **007**-**008**:
- Connect signal `clicked()` of QPushButton with slot `quit()` of QApplication
through `QObject::connect()` method.
    - SIGNAL() and SLOT() macros are specified arguments help `connect()` binds
        signal with slot.