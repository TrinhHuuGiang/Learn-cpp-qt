## Content
- [Signal and slot](#signal-and-slot)

---

## Signal and slot
*The signals and slots mechanism is fundamental to Qt programming. It enables the application programmer
to bind objects together without the objects knowing anything about each other.*

- It only available when class is derived from QObject and 
has **Q_OBJECT** macro at start of class.
- The **Q_OBJECT** help Qt parser while preprocessing know
this is QObject, handle `signal` `slot` `emit` macro inside class.
- Then register class into  Qt’s meta-object system through `Qt’s moc tool` (Meta Object Compiler)

---

**Slots** are almost identical to ordinary C++ member functions:
- **can be**: virtual, overloaded | public, protected, private | and has it own parameters.

---

The **connect()** method from `QObject` using macro **SIGNAL()** and **SLOT()** to convert signal and slot functions into signature strings.
- First parameter is **pointer to QObject own signal** want to connect with other **slot**.
- Third parameter is **pointer to QObject receive signal** with it **slot**.

```cpp
// 1 signal to many slots
connect(slider, SIGNAL(valueChanged(int)),
spinBox, SLOT(setValue(int)));

connect(slider, SIGNAL(valueChanged(int)),
this, SLOT(updateStatusBarIndicator(int)));

// Many signal to the same slot
connect(lcd, SIGNAL(overflow()),
this, SLOT(handleMathError()));

connect(calculator, SIGNAL(divisionByZero()),
this, SLOT(handleMathError()));

// A signal can be connected to another signal
connect(lineEdit, SIGNAL(textChanged(const QString &)),
this, SIGNAL(updateRecord(const QString &)));
```

Notice:
- The `signal` must have the same parameters the `slot` required.
- The `signal` can has more than paramters `slot` required and remain will be ignore.
- Qt will warning in debug mode if signal and slot not match parameters.


---

The **disconnect()** method remove signal-slot pair.  
*This is rarely needed, because Qt automatically removes all connections
involving an object when that object is deleted.*

--- 

