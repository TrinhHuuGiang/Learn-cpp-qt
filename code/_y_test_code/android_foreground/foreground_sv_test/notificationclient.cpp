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
    // connect
    connect(this, SIGNAL(notificationChanged()), this, SLOT(updateAndroidNotification()));

    // start foreground service
    startAndroidNotification();
}

void NotificationClient::startAndroidNotification()
{
#if defined(Q_OS_ANDROID)
    auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());
    QAndroidIntent serviceIntent(activity.object(),
                                "opensource/giangtrinh/fgsv_test/src/NotificationClient");
    QJniObject result = activity.callObjectMethod(
        "startService",
        "(Landroid/content/Intent;)Landroid/content/ComponentName;",
        serviceIntent.handle().object());
#endif

    qDebug() << this<< "called start notification !";
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


// [Example code: Notification]
void NotificationClient::updateAndroidNotification()
{
#if defined(Q_OS_ANDROID)
    auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());

    // Tạo một Intent trỏ thẳng tới NotificationClient Service
    QAndroidIntent updateIntent(activity.object(), "opensource/giangtrinh/fgsv_test/src/NotificationClient");

    // Gán Action và chuỗi thông điệp mới vào Intent
    QJniObject actionString = QJniObject::fromString("UPDATE_NOTIFICATION");
    QJniObject messageString = QJniObject::fromString(m_notification);

    updateIntent.handle().callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", actionString.object());
    updateIntent.handle().callObjectMethod("putExtra", "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
                                           QJniObject::fromString("message").object(), messageString.object());

    // Gửi Intent kích hoạt onStartCommand của Service để thực hiện cập nhật
    activity.callObjectMethod(
        "startService",
        "(Landroid/content/Intent;)Landroid/content/ComponentName;",
        updateIntent.handle().object());
#endif
}


