#include "iconeditorplugin.h"

#include "iconeditor.h"

IconEditorPlugin::IconEditorPlugin(QObject *parent)
    : QObject{parent}
{}

bool IconEditorPlugin::isInitialized() const
{
    return initialized;
}

void IconEditorPlugin::initialize(QDesignerFormEditorInterface * /* core */) // core unused now
{
    if (initialized)
        return;

    initialized = true;
}

QString IconEditorPlugin::name() const
{
    return "IconEditor";
}

QString IconEditorPlugin::includeFile() const
{
    return "iconeditor.h";
}

QString IconEditorPlugin::group() const
{
    return tr("Image Manipulation Widgets");
}

QIcon IconEditorPlugin::icon() const
{
    return QIcon(":/images/iconeditor.png");
}

QString IconEditorPlugin::toolTip() const
{
    return tr("An icon editor widget");
}

QString IconEditorPlugin::whatsThis() const
{
    return tr("This widget is presented in Chapter 5 of <i>C++ GUI "
              "Programming with Qt 4</i> as an example of a custom Qt "
              "widget.");
}

bool IconEditorPlugin::isContainer() const
{
    return false;
}

QWidget *IconEditorPlugin::createWidget(QWidget *parent)
{
    return new IconEditor(parent);
}



// Source - https://stackoverflow.com/a/22395411
// Posted by László Papp
// Retrieved 2026-05-01, License - CC BY-SA 3.0

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(iconeditorplugin, IconEditorPlugin);
#endif
