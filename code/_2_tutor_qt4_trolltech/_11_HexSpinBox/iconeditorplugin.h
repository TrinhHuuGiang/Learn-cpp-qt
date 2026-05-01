#ifndef ICONEDITORPLUGIN_H
#define ICONEDITORPLUGIN_H

#include <QObject>
#include <QDesignerCustomWidgetInterface>   // F1 for more inform implement this plugin library

class IconEditorPlugin : public QObject,
                         public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)


// Source - https://stackoverflow.com/a/22395411
// Posted by László Papp
// Retrieved 2026-05-01, License - CC BY-SA 3.0
    #if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        // Q_PLUGIN_METADATA(IID "your-string-here" FILE "file-here-but-can-be-empty")
        Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")   // F1 on include <QDesignerCustomWidgetInterface>
    #endif


public:
    explicit IconEditorPlugin(QObject *parent = nullptr);

// New from Qt 5-6
    bool isInitialized() const; //override;
    void initialize(QDesignerFormEditorInterface *core); //override;


// Old from Qt4
    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget *createWidget(QWidget *parent);


private:
    bool initialized = false;

};

#endif // ICONEDITORPLUGIN_H
