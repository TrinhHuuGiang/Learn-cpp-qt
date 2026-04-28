Follow project: **Spreadsheet**

---

Morden Main Window GUI provide some: *menu*s, *context menus* (right click), *toolbars*

![menu and toolbar](./rss/_11_menu_toolbar.png)

Qt using the **actions** handle contexts inside them:
- Create and set up the actions.
- Create menus and populate them with the actions.
- Create toolbars and populate them with the actions.

---

## Content
- [Create action in MainWindow](#create-action-in-mainwindow)
    - the [New](#new-action) action.

- [Create a menu containing actions]()
    - the **menuBar()** of *QMainWindow*

---

## Create action in MainWindow
The term **action** is an object has some properties:

- Label and/or Icon
    - Label can include **&** to add a buddy, this optional or using shortcut below.
- A combined shortcut Key: example Ctrl + Shift + N 
- A status line help, show when hover on
- A **signal** when clicked can make connection.

---

### `New` action 
Properties:
- Main class is **QAction**
    ```cpp
        // Label and parent:
        newAction = new QAction(tr("&New"), this);
        newAction->setIcon(QIcon(":/images/new.png"));
        // Shortcut
        newAction->setShortcut(tr("Ctrl+N"));
        // Status
        newAction->setStatusTip(tr("Create a new spreadsheet file"));
        // Signal: triggered()
        connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    ```

---

## Create a menu containing actions
The *QMainWindow* has a **QMenuBar** can add some *QMenu Widget* inside it:
- The *QMenuBar* can access by **menuBar()**, it automatically create 
new *QMenuBar* at first call.
    - *QMenuBar* can contain some *QMenu*
    - *QMenuBar* with method **addSeparator()** add a vertical line between each *QMenu*
- The *QMenu* can contain some *Action*

Example:

```cpp
fileMenu = menuBar()->addMenu(tr("&File"));
fileMenu->addAction(newAction);
fileMenu->addAction(openAction);
fileMenu->addAction(saveAction);
fileMenu->addAction(saveAsAction);
separatorAction = fileMenu->addSeparator();
for (int i = 0; i < MaxRecentFiles; ++i)
fileMenu->addAction(recentFileActions[i]);
fileMenu->addSeparator();
fileMenu->addAction(exitAction);
```

