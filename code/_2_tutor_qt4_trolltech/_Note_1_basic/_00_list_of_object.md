This section focus on collects and groups any QObject:  
method `mt`, signal `sn`, slot `sl`, function `f`, macros `mr`,
... available when design Widget GUI.

May try type any result below into QtCreator then click, type `F1` to see it
documentation.

Index:
- [QObject](#qobject)
- [Widgets management object](#qt-widgets-management-object)
- [Widget container](#widget-container)
- [Widget layout](#widget-layout)
- [Widget](#widget)
- [String format]()
- [Qt namespace]()
---

### QObject
- **QObject**: 
    - `mt` connect(), `mr` SIGNAL(), SLOT()
    - Classes: 
        - header: `mr` Q_OBJECT, signal, private slot
        - source: `mr` emit
- **QRegularExpression** create a validator with input **QRegularExpression** rule.
    - Sometime using as child of widget input: `QLineEdit`

---

###  Qt widgets management object
- **QApplication**: `mt` exect(), `sl` quit()

---

### Widget container
- **QWidget**: 
    - `mt` setWindowTitle(), setLayout(), QWidget::setTabOrder()
    - `mt` setVisible(), show(), showFullScreen(), showMaximized(), showMinimized(), showNormal()
    - **QMainWindow**, **QDialog** are inherited
- **QMainWindow**: `mt` setWindowTitle(), setLayout()
- **QDialog**: 
    - `mt` setWindowTitle(), setLayout(), setFixedHeight(), sizeHint()
    - `mt` exec(), show(), `sl` accept(), reject()

---

### Widget layout
- **QHBoxLayout** (left to right): `mt` addWidget(), addStretch()
- **QVBoxLayout** (high to low): `mt` addWidget()
- **QGridLayout** (coordinate): `mt` addWidget()


---

### Widget
- **QLabel**: `mt` show()
- **QLineEdit**: `mt` hasAcceptableInput(), `sn` textChanged()

- **QPushButton**: `mt` setDefault(), setEnabled(), `sn` clicked()
- **QCheckBox**: `mt` isChecked()

- **QSlider**:  `mt` setRange(), `sn` valueChanged(), `sl` setValue()
- **QSpinBox**: `mt` setRange(), `sn` valueChanged(), `s;` setValue()

- **QComboBox**: `sl` setVisible()

---

### String format
- **"this is string"**: normal string.
- **tr("this is string")**: mark string can be translated if required.
- **"this is &string"**: `& or ampersands` indicate shortcut key is next 1 character.
    - Using `Alt` to show shortcut key, `Alt + shotcut` to fucus on buddy object.

- **QString** 

- **QRegularExpression** make regular exparession rule
- **QRegularExpressionValidator** create a validator with input **QRegularExpression**

---

### Qt namespace
- namespace `Qt`: contains miscellaneous identifiers used throughout the Qt library.
    - enum `Qt::CaseSensitivity`