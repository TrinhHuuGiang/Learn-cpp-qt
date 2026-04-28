Initialize project: **Spreadsheet**


## References
- Clone source code: https://www.informit.com/store/c-plus-plus-gui-programming-with-qt4-9780132354165

After build, fix missing all on Window:

- Fix missing dll: https://www.qtcentre.org/threads/62050-I-cannot-run-my-executable-file(exe-file)!
    - Find all dll required, search in: Qt_install_folder/6.5.3/mingw_64/bin/
        - 6.5.3 or other version QtCreator used to build application.
    - Put into same folder of executation file.
- Fix no Qt platform plugin: https://falsinsoft.blogspot.com/2013/09/qt-5-and-failed-to-load-platform-plugin.html
    - Find `qwindows.dll` in: Qt_install_folder/6.5.3/mingw_64/plugins/platforms
    - Creat a folder `platforms` in same folder of executation file, put `qwindows.dll` here

## Openning with some highlight content
- [Reimplement the closeEvent()](#reimplement-the-closeevent)

- [Qt resoure system](#qt-resoure-system)
    - **qrc** has path prefix for resource from root: **:/**

- [setWindowIcon()]()
    - Only set window icon, can't set desktop icon
    - Desktop icon depend on each OS, implement out side the program


---

## Reimplement the closeEvent()
```cpp
    void MainWindow::closeEvent(QCloseEvent *event)
    {
        if (okToContinue()) 
        {
            writeSettings();
            event->accept();
        } else {
            event->ignore();
        }
    }
```
- Everytime user click `X` on window, Qt callback to virtual method `closeEvent()`
with argument `QCloseEvent *event`
    - If **event->accept();** 
    - Else **event->ignore();** to prevent close the window
    - Default not 

---

## Qt resoure system
1. **Right click project -> Add new -> Qt -> Qt Resource File**
1. Set file name.
1. After `file.qrc` exist, right click -> Open with:
    - *Resource Editor* for UI configuration
        - Now add **prefix** then click add **Add Files** to add file.
        - link to file == *:/prefix/link_from_root_project_folder*
    - *Plain text editor* open XML editor
        ```XML
            <RCC>
            <qresource>
                <file>images/icon.png</file>
                <!-- ... More -->
                <file>images/find.png</file>
                <file>images/gotocell.png</file>
            </qresource>
            </RCC>
        ```
        - access file with link format *link to file* above

---

## setWindowIcon()
Example take file from **.qrc**:
```cpp
    setWindowIcon(QIcon(":/images/icon.png"));
```

