QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# ===BUILD WIDGET PLUGIN for DESIGN MODE====
# => uncomment: build plugin
# => comment: build
#
# follow:
# - https://doc.qt.io/qt-6/qtdesigner-customwidgetplugin-example.html
# - https://doc.qt.io/qt-6/qdesignercustomwidgetinterface.html
#
# After make plugin, found at:
# - D:\...\Qt\Installtion\6.5.3\mingw_64\plugins\designer (Window)
# - Same with other platforms
#
# Then must copy the generated .dll
# - into: D:\...\Qt\Installtion\Tools\QtCreator\bin\plugins\designer
#

QT += designer uiplugin
CONFIG += plugin
TEMPLATE = lib
DESTDIR = $(QTDIR)/plugins/designer   #old in Qt4 but working, generated .dll file

# TARGET = $$qtLibraryTarget($$TARGET)  # Not working
# target.path = $$[QT_INSTALL_PLUGINS]/designer
# INSTALLS += target

# ==========================================



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hexspinbox.cpp \
    iconeditor.cpp \
    iconeditorplugin.cpp \
    main.cpp

HEADERS += \
    hexspinbox.h \
    iconeditor.h \
    iconeditorplugin.h

FORMS += \
    hexspinbox.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rss.qrc
