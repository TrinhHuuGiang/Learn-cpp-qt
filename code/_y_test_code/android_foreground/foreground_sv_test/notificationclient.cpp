#include "notificationclient.h"


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



NotificationClient::NotificationClient(QObject *parent)
    : QObject{parent}
{
    connect(this, SIGNAL(notificationChanged()), this, SLOT(updateAndroidNotification()));
}

void NotificationClient::setNotification(const QString &notification)
{
    m_notification = notification;
    emit notificationChanged();
}

void NotificationClient::setNotificationHappy()
{
    setNotification("The user is happy!");
}
void NotificationClient::setNotificationSad()
{
    setNotification("The user is sad!");
}



void NotificationClient::updateAndroidNotification()
{
    QJniObject javaNotification = QJniObject::fromString(m_notification);
    QJniObject::callStaticMethod<void>(
        "NotificationClient",
        "notify",
        "(Landroid/content/Context;Ljava/lang/String;)V",
        QNativeInterface::QAndroidApplication::context(),
        javaNotification.object<jstring>());
}
