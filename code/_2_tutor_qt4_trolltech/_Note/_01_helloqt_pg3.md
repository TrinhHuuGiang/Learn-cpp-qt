## Content
- [Example Hello Qt](#hello-qt): 
    - Briefly describe the main function of a Qt program.
    - Some Qt objects: application management object, widget, and some
    their method.
    - Build application by Qt Creator 6.5

## What news:
- management object:
    - QApplication: method exect()
- widget:
    - QLabel: method show()

## Hello Qt
```cpp
001 #include <QApplication>
002 #include <QLabel>
003 int main(int argc, char *argv[])
004 {
005 QApplication app(argc, argv);
006 QLabel *label = new QLabel("Hello Qt!");
007 label->show();
008 return app.exec();
009 }
```

---

Line **003**: Qt support command line application, with `argc` and `argv` as normal C++ source code.  
Line **005**: `QApplication` is object manages all application resources,
it is main object, requires `argc` and `argv`.

---

Line **006**: `QLabel` object is a `widget` that displays string "Hello Qt!".  
- The term *widget* is a visual element in user interface.
- A few other *widget*'s as: button, sroll bar,...
- A widget can contains other widgets.
- Most of application using `QMainWindow` or `QDialog` as application window.
but not only those, any Qt widget can the main window, example `QLabel` above.

Line **007**: Widget's default are hidden; we can customize them before display, avoid
unwanted content.
- Method `show()` is using to display it. 

--- 

Line **008**: After configure widget done, passes the control of application to Qt through management object as `QApplication` in this example.
- The method `exec()` make `QApplication` run an event loop to check any
user action emit a signal. Example: a widget is clicked, mouse release,...

--- 

The last one, deallocator `delete` should call to clean memory.
- In this example has memory leak, the QLabel `label` is ignored but memory will be reclaimed by OS after application closed.

After create a project by Qt Creator, it automatically generates `.pro` file.
That is configuration project file helps build tools `qmake` build application.


