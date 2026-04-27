This section will test the Qt built-in *Widgets* and some *Dialog classes*.

## References   
- [Qt application automatically exit after all window is hidden](https://stackoverflow.com/questions/55064660/qt-application-exit-automatically-when-mainwindow-is-hidden)

## Content
- [Built in Widgets](#build-in-widgets)
- [Built in Dialogs](#built-in-dialogs)
    - After click `X` window dialog, it will `close()` 
    - QApplication `exit()` by default after all window hiden by `hide()` or `close()`(no window visibility)    
        - It depend on default option **QApplication::quitOnLastWindowClosed(true);**

---

## Build-in Widgets

1. Button widgets:
- **QPushButton**: A button with string label on it
    - It can act like a toggle button or just push button
    - It support icon with text by method **setIcon()** and **setText()**
- **QToolButton**: Like a push button but has extra features:
    - Display icon, text make highlight the tool behaviors.
    - It text quite long than button, change by `...`. Example: Tool button -> To...on
    - Create a **Popup** menu with multiple option by method `setPopupMode()`.
- **QCheckBox**: A square box can tick on it
- **QRadioButton**: A Circle box can tick on it
    - radio boxs in the same scope like Widget, layout mutual exclusive others (only one box checked).

![Button widgets](./rss/_09_widget_buttons.png)
![Button widgets](./rss/_09_widget_buttons_2.png)

---

1. Display widget
- **QLabel**, **TextBrowser**
- **QLCDNumber**, **QProgressBar**
- **QSpinBox**, **QDoubleSpinBox**
- **QComboBox**
- **QDateEdit**, **QTimeEdit**, **QDateTimeEdit**
- **QScrollBar**, **Slider**, **QDial**
- **QTextEdit**

---

1. Container widget:
- **QFrame**
    - Same with **QWidget**, addition is has frame.
- **QGroupBox**
    - Has frame + Title
- **QToolBox** 
    - Each new page title stacked on oldpage, take amount vertical space
    - Only suitable if few page, icon ToolButton 
- **QTabWidget**
    - Like **GroupBox** but multiple pages, tab bar change page
    - Numbered from 0
- **QScrollArea**
    - If mainpage bigger than parent Widget, appear scroll bar
- **QStackedWidget**
    - Like **QTabWidget** but multiple pages without tab bar to change page
    - Using when custom button to change page or handle display page follow event

---

1. View widget
- QListView
- QTreeView
- QTableView

---

## Built in Dialogs

- **QColorDialog**
- **QFontDialog**
- **QFileDialog**
- **QInputDialog**
- **QProgressDialog**
    - By default it will show after initialized.
    - It take default 4second before show
- **QMessageBox**
- **QErrorMessage**
