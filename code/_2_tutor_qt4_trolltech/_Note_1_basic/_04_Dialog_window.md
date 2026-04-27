## Content
Dialog box presents options and choices for user make their choices.  

- [Create a QDialog class](#create-a-qdialog-class): 
    - [Create QDialog class](#create-a-qdialog-class)
    - About QObject
        - QObject can't copy
    - [About signal and slot](#qobject-signal-and-slot)

---

## Create a QDialog class
In project folder created by Qt Creator:
- Right click -> Add new -> Qt ->  
    Qt Widgets Designer From Class
- Here has some template classes:
    - Dialog without Button (a blank dialog) or with Button
    - Main Window
    - Widget
- Set class name, header, source, ui, all should has the same name,...
    - In this test documentation, class name is `FindDialog`

---

After create, `findialog.h` seem like that:
```cpp
001 #ifndef FINDDIALOG_H
002 #define FINDDIALOG_H
003 #include <QDialog>
004 class QCheckBox;
005 class QLabel;
006 class QLineEdit;
007 class QPushButton

008 class FindDialog : public QDialog
009 {
010 Q_OBJECT
011 public:
012 FindDialog(QWidget *parent = 0);
```

Some notices about a `QObject` class:
1. `QObject` is base class for all Qt element from widget, layout, container or custom 
derived class from `QObject`. It provides two important functions:
    - Signal/slot system: communication between objects
    - Parent-child ownership: delete child while parent is being deleted.

1. `Q_OBJECT` macro must at beginning and private section of class.  
Will defines necessaries for object class working as a `QObject` with signal and slot mechanism.

1. In constructor `FindDialog(QWidget *parent = 0);`, the parameter **parent**
is compulsory.
    - Each `QObject base` object can become child of anothers by the **parent** pointer. By default it is nullptr, meaning that is parent.


---

### QObject signal and slot
**signals** and **slots** in Qt work as communication model `publish-subscribe`,
where one signal emits to one or some slots to perform specific behaviors.

---

```cpp
013 signals:
014 void findNext(const QString &str, Qt::CaseSensitivity cs);
015 void findPrevious(const QString &str, Qt::CaseSensitivity cs);
```

**signals** is a macro, read by Qt C++ preprocessor before convert
into standard C++. Then compiler can handles it.
- Declared methods inside signal will be managed by Qt Meta-Object Compiler (MOC) in preprocessing phase.
- Then it can bind with another **slots** through **QObject::connect()** method.

---

```cpp
016 private slots:
017 void findClicked();
018 void enableFindButton(const QString &text);

020 QLabel *label;
021 QLineEdit *lineEdit;
022 QCheckBox *caseCheckBox;
023 QCheckBox *backwardCheckBox;
024 QPushButton *findButton;
025 QPushButton *closeButton;
026 };
027 #endif
```

**slots** like **signals** is a macro, that expands into a
construct that the C++ compiler can handles.
- Infact, **slots** are methods user must define to react with
any **signal** binded through **QObject::connect()** method.
    - **slots** like normal method, can call normal method, limited by class access specifier(private, protected, public). 
    - In this example it private and will be managed by Qt Meta-Object Compiler (MOC), 
    **QObject::connect()** can access with no limit from access specifier.

---

### Source code

```cpp

003 FindDialog::FindDialog(QWidget *parent)
004 : QDialog(parent)
005 {

006 label = new QLabel(tr("Find &what:"));
007 lineEdit = new QLineEdit;
008 label->setBuddy(lineEdit);

009 caseCheckBox = new QCheckBox(tr("Match &case"));
010 backwardCheckBox = new QCheckBox(tr("Search &backward"));

011 findButton = new QPushButton(tr("&Find"));
012 findButton->setDefault(true);
013 findButton->setEnabled(false);
014 closeButton = new QPushButton(tr("Close"));

015 connect(lineEdit, SIGNAL(textChanged(const QString &)),
016 this, SLOT(enableFindButton(const QString &)));
017 connect(findButton, SIGNAL(clicked()),
018 this, SLOT(findClicked()));
019 connect(closeButton, SIGNAL(clicked()),
020 this, SLOT(close()));

021 QHBoxLayout *topLeftLayout = new QHBoxLayout;
022 topLeftLayout->addWidget(label);
023 topLeftLayout->addWidget(lineEdit);

024 QVBoxLayout *leftLayout = new QVBoxLayout;
025 leftLayout->addLayout(topLeftLayout);
026 leftLayout->addWidget(caseCheckBox);
027 leftLayout->addWidget(backwardCheckBox);

028 QVBoxLayout *rightLayout = new QVBoxLayout;
029 rightLayout->addWidget(findButton);
030 rightLayout->addWidget(closeButton);
031 rightLayout->addStretch();

032 QHBoxLayout *mainLayout = new QHBoxLayout;
033 mainLayout->addLayout(leftLayout);
034 mainLayout->addLayout(rightLayout);
035 setLayout(mainLayout);

036 setWindowTitle(tr("Find"));
037 setFixedHeight(sizeHint().height());
038 }


039 void FindDialog::findClicked()
040 {
041 QString text = lineEdit->text();
042 Qt::CaseSensitivity cs =
043 caseCheckBox->isChecked() ? Qt::CaseSensitive
044 : Qt::CaseInsensitive;
045 if (backwardCheckBox->isChecked()) {
046 emit findPrevious(text, cs);
047 } else {
048 emit findNext(text, cs);
049 }
050 }
051 void FindDialog::enableFindButton(const QString &text)
052 {
053 findButton->setEnabled(!text.isEmpty());
054 }
```

Line **006**-**008**: the tr() wrap a string, mark them for translation to other languages.
- tr() is defined in QOBJECT macro in every derived QObject classes.
- It should place where string need show to user, is optional but 
good if has plan for translating in future.

The `&` or ampersand indicates a shortcut key by first character of word
after it.
- It sometime detect by `QLabel` to display and **setBuddy()** method to select
destination `Widget` (can focus) forward to. 
- Using `Alt + character` to active shortcut.
- Push `Alt` if shortcut key not show underline.

---

Line **009**-**014**: 
- `QCheckBox` and `QPushButton` has it own label, don't need set buddy, just string with `&`.
- `QPushButton` with method `setDefault` will highlight and
focus to this button.
- when method `setEnabled` decide click available on button. If false button
can't click.

---

Line **015** - **020**:
- `QLineEdit` emit signal `textChanged()` every time user typing on it.

---

Lint **031**:
- `QHBoxLayout`: method `addStretch()` add a spacer fill remain space.

---

Line **036**-**037**:
- The `QDialog` has method:
    - `setFixedHeight()` after set height, fix it can't resize.
    - `sizeHint()` automatically calculate suitable size, margin for QBbject's inside.

---

Line **041**-**043**:
- `QLineEdit` with method `text()` return a `QString` object
- `Qt` is the namespace, contains miscellaneous identifiers used throughout the Qt library.
    - `Qt::CaseSensitivity` is enum case sensitivity or not
- `QCheckBox`: method `isChecked()` return bool

--- 

Extra:
- Push `Tab` order: by default when push Tab, default focus with change to next 
Widget follow by order in which widgets were created.
    - `QWidget::setTabOrder(a,b)` help adjust order Widget a -> Widget b in Tab chain