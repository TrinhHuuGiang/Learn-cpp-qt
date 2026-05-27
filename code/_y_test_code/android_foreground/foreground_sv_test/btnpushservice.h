#ifndef BTNPUSHSERVICE_H
#define BTNPUSHSERVICE_H

#include <QtVersionChecks>
/* Qt system detection */
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
// refer: https://doc.qt.io/qt-6/qtsystemdetection.html
#include <QtSystemDetection>
#else
// refer: https://www.qthub.com/static/doc/qt5/qtcore/qtglobal.html
#include <QtGlobal>
#endif

#if defined(Q_OS_ANDROID)
#include <QtCore/private/qandroidextras_p.h>
#endif

#include <QPushButton>


class BtnPushService : public QPushButton
{
    Q_OBJECT

private slots:
    void start_service_test()
    {
#if defined(Q_OS_ANDROID)
        auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());
        QAndroidIntent serviceIntent(activity.object(),
                                     "QtAndroidService");
        QJniObject result = activity.callObjectMethod(
            "startService",
            "(Landroid/content/Intent;)Landroid/content/ComponentName;",
            serviceIntent.handle().object());
#endif

        qDebug() << this<< "clicked";
    }

public:
    BtnPushService(QWidget* parent = nullptr):QPushButton{parent}
    {
        connect(this, SIGNAL(clicked(bool)), this, SLOT(start_service_test()));
    }
};

#endif // BTNPUSHSERVICE_H
