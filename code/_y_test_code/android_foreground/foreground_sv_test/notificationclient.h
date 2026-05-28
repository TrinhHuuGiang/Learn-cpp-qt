/*
 * Refer from: https://doc.qt.io/qt-6.8/qtcore-platform-androidnotifier-example.html
 */

#ifndef NOTIFICATIONCLIENT_H
#define NOTIFICATIONCLIENT_H

#include <QObject>

#include <QString>

class NotificationClient : public QObject
{
    Q_OBJECT
public:
    explicit NotificationClient(QObject *parent = nullptr);

private:
    void startAndroidNotification();

    void setNotification(const QString &notification);
    // QString notification() const;

private slots:
    void setNotificationHappy();
    void setNotificationSad();

signals:
    void notificationChanged();

private slots:
    void updateAndroidNotification();

private:
    QString m_notification;
};

#endif // NOTIFICATIONCLIENT_H
