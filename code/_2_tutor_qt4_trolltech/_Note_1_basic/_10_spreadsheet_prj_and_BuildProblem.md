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

After build, fix some android build application issue
- Build `apk` for Qt5 framework if require lower JDK version: 
    - https://doc.qt.io/qt-6.5/android-deploy-qt-tool.html
    - Test on Qt 5.15.2 https://github.com/TrinhHuuGiang/Learn-cpp-qt/blob/12ef8609d20a0fa69be258320b09ad485c14dcc0/code/_x_Note/_qt5_android_21.txt
- Check which android platform `apk` supported: https://stackoverflow.com/questions/8300822/android-how-to-find-which-platform-version-an-apk-targets 
- Fix `apk` built not expected platform (v7a, v8a, x86,...): https://forum.qt.io/topic/131620/qt-5-15-2-clang-multi-abi-issue-no-arm64-build/2

- Debug tools android:
    - Control screen and install app: **scrcpy**
    - Log debug, find **adb** program in Qt directory install the SDK:
        - Sometime found at: *SDK -> platform-tools *
        - Or sometime if following with **scrcpy** package


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

