This section focus on collects and groups any QObject:  
method `mt`, signal `sn`, slot `sl`, function `f`, macros `mr`, virtual `vt`
... available when design Widget GUI.

May try type any result below into QtCreator then click, type `F1` to see it
documentation.

Index:
- [QObject](#qobject)
- [Widgets management object](#qt-widgets-management-object)
- [Widget container](#widget-container)
- [Widget viewer](#widget-viewer)
- [Widget layout](#widget-layout)
- [Widget](#widget)
- [String format](#string-format)
- [Qt namespace](#qt-namespace)
- [Some build-in Dialog](#some-build-in-dialog)

---

### QObject
- **QObject**: 
    - `mt` connect(), `mr` SIGNAL(), SLOT()
    - Classes: 
        - header: 
            - `mr` Q_OBJECT, signal, private slot
            - `mr` _Q_PROPERTY(  
                **property type**  property_name  
                **READ**  read_func/getter  
                **WRITE (optional)**  write_func/setter  
                ... and more)
                - set custom properties exist in Qt UI Design mode
                - setup after Q_OBJECT
                - _Q_PROPERTY more information `F1` in QtCreator

        - source: `mr` emit


- **QRegularExpression** create a validator with input **QRegularExpression** rule.
    - Sometime using as child of widget input: `QLineEdit`

---

###  Qt widgets management object
- **QApplication**: `mt` exect(), `sl` quit(), exit()

---

### Widget container
- **QWidget**: 
    - **QMainWindow**, **QDialog** are inherited
    - `mt` setWindowTitle(), setLayout(), QWidget::setTabOrder()
    - `mt` setWindowIcon
    - `mt` setFixedHeight(), setFixedWidth(), sizeHint()->height(),...
    - `mt` setSizeConstraint()
    - `mt` showFullScreen(), showMaximized(), showMinimized(), showNormal()
    - `sl` setVisible(), show(), hide(), close() 
    - `mt` *virtual* closeEvent(QCloseEvent *event)
        - event->accept(); event->ignore();

- **QMainWindow**: 
    - `mt` statusBar()->addWidget(), `sl` updateStatusBar()
    - `mt` setCentralWidget()

- **QDialog**: 
    - `mt` exec(), `sl` accept(), reject()

---

- **QFrame**
- **QGroupBox**
- **QToolBox**
- **QTabWidget**

- **QScrollArea**
- **QStackedWidget**

---

### Widget viewer
- **QListView**
- **QTreeView**
- **QTableView**

---

### Widget layout
- **QHBoxLayout** (left to right): `mt` addWidget(), addStretch()
- **QVBoxLayout** (high to low): `mt` addWidget()
- **QGridLayout** (coordinate): `mt` addWidget()

---

### Widget
- **QLabel**: `mt` show(), setAlignment(), setIndent()
- **QLineEdit**: `mt` hasAcceptableInput(), `sn` textChanged()

- **QPushButton**: 
    - `mt` setDefault(), setEnabled(), `sn` clicked()
    - `mt` setCheckable(), setChecked() `sn` toggled()
- **QCheckBox**: `mt` isChecked()

- **QSlider**:  `mt` setRange(), `sn` valueChanged(), `sl` setValue()
- **QSpinBox**: `mt` setRange(), `sn` valueChanged(), `s;` setValue()
    - `mt` `vt` textFromValue(),  valueFromText(), validate()

- **QComboBox**: `mt` clear(), addItem(), `sl` setVisible()

---

### String format
- **"this is string"**: normal string.
- **tr("this is string")**: mark string can be translated if required.
- **"this is &string"**: `& or ampersands` indicate shortcut key is next 1 character.
    - Using `Alt` to show shortcut key, `Alt + shotcut` to fucus on buddy object.

- **QString** 

- **QRegularExpression** make regular exparession rule
- **QRegularExpressionValidator** create a validator with input **QRegularExpression**

- **QChar**

---

### Qt namespace
- namespace `Qt`: contains miscellaneous identifiers used throughout the Qt library.
    - enum `Qt::CaseSensitivity`

---

### Some build-in Dialog
- **QColorDialog**
- **QFontDialog**
- **QFileDialog**
- **QInputDialog**
- **QProgressDialog**
- **QMessageBox**
- **QErrorMessage**