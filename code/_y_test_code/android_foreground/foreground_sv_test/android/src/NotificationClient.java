/*

Copy from: https://doc.qt.io/qt-6.8/qtcore-platform-androidnotifier-example.html
Refer QtAndroidService.java: find in same folder

Refer Android API: https://developer.android.com/reference/packages

*/

// package org.qtproject.example.androidnotifier;

package opensource.giangtrinh.fgsv_test.src;

import android.app.Notification;
import android.app.NotificationManager;

import android.content.Context;
import android.content.Intent;              // Addition from: QtAndroidService example
import android.util.Log;
import org.qtproject.qt.android.bindings.QtService;

import android.content.pm.ServiceInfo;

import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.BitmapFactory;
import android.app.NotificationChannel;

import opensource.giangtrinh.fgsv_test.R;   // see package path in AndroidManifest

public class NotificationClient extends QtService
{
    private static final String TAG = "NotificationClientService";
    private static final String CHANNEL_ID = "QtServiceChannel";
    private static final int NOTIFICATION_ID = 1; // Giữ nguyên ID cố định để cập nhật liên tục

    @Override
    public void onCreate()
    {
        super.onCreate();
        Log.i(TAG, "Creating Service");

        // Tạo kênh thông báo (Notification Channel) cho Android O trở lên
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O)
        {
            NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
            NotificationChannel channel = new NotificationChannel(
                    CHANNEL_ID,
                    "Qt Foreground Service",
                    NotificationManager.IMPORTANCE_LOW);
            manager.createNotificationChannel(channel);
        }

        // Khởi tạo thông báo mặc định ban đầu khi Service chạy
        Notification notification = buildNotification("Foreground service running");

        // Đưa dịch vụ lên chế độ Foreground
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.Q) {
            startForeground(NOTIFICATION_ID, notification,
                    ServiceInfo.FOREGROUND_SERVICE_TYPE_DATA_SYNC);
        } else {
            startForeground(NOTIFICATION_ID, notification);
        }
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
        Log.i(TAG, "Destroying Service");
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        int ret = super.onStartCommand(intent, flags, startId);
        Log.i(TAG, "Starting Command");

        // Đón Intent cập nhật từ C++ gửi sang
        if (intent != null && "UPDATE_NOTIFICATION".equals(intent.getAction())) {
            String message = intent.getStringExtra("message");
            if (message != null) {
                updateForegroundNotification(message);
            }
        }

        return ret;
    }


    // Helper method dùng chung để đóng gói cấu trúc Notification
    private Notification buildNotification(String message) {
        Notification.Builder builder;

        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
            builder = new Notification.Builder(this, CHANNEL_ID);
        } else {
            builder = new Notification.Builder(this);
        }

        Bitmap icon = BitmapFactory.decodeResource(getResources(), R.drawable.sunset);

        builder
                .setSmallIcon(R.drawable.sunset)
                .setLargeIcon(icon)
                .setContentTitle("A message from Qt!")
                .setContentText(message)
                .setDefaults(Notification.DEFAULT_SOUND)
                .setColor(Color.GREEN)
                .setOngoing(true); // Luôn luôn gán trạng thái chạy ngầm cố định

        return builder.build();
    }

    // [Object Method]: Cập nhật trực tiếp nội dung lên Foreground Notification hiện tại
    public void updateForegroundNotification(String message) {
        try {
            NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
            Notification updatedNotification = buildNotification(message);

            // Gọi notify với ID trùng với ID ban đầu (1) sẽ làm mới thanh trạng thái ngay lập tức
            manager.notify(NOTIFICATION_ID, updatedNotification);
            Log.i(TAG, "Foreground Notification updated with text: " + message);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }



// // [Example code: Notification]
//     public static void notify(Context context, String message) {
//         try {
//             NotificationManager m_notificationManager = (NotificationManager)
//                     context.getSystemService(Context.NOTIFICATION_SERVICE);

//             Notification.Builder m_builder;
//             if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
//                 int importance = NotificationManager.IMPORTANCE_DEFAULT;
//                 NotificationChannel notificationChannel;
//                 notificationChannel = new NotificationChannel("Qt", "Qt Notifier", importance);
//                 m_notificationManager.createNotificationChannel(notificationChannel);
//                 m_builder = new Notification.Builder(context, notificationChannel.getId());
//             } else {
//                 m_builder = new Notification.Builder(context);
//             }

//             Bitmap icon = BitmapFactory.decodeResource(context.getResources(), R.drawable.sunset);
//             m_builder
//                     .setSmallIcon(R.drawable.sunset)
//                     .setLargeIcon(icon)
//                     .setContentTitle("A message from Qt!")
//                     .setContentText(message)
//                     .setDefaults(Notification.DEFAULT_SOUND)
//                     .setColor(Color.GREEN)
//                     .setAutoCancel(true);

//             m_notificationManager.notify(0, m_builder.build());
//         } catch (Exception e) {
//             e.printStackTrace();
//         }
//     }


}
