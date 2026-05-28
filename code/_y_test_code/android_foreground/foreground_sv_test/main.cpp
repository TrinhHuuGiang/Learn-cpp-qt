/*
 * References:
 * 1. Deploy applications on android :
 *      https://doc.qt.io/qt-6/deployment-android.html
 * 2. Qt Android services:
 *      https://doc.qt.io/qt-6.5/android-services.html
 * 3. Android background and foreground
 *      https://developer.android.com/develop/background-work/services/fgs?hl=en
 * 4. Android app resources:
 *      https://developer.android.com/guide/topics/resources/providing-resources
 * 5. Create, add app icon on launcher:
 *      https://developer.android.com/codelabs/basic-android-kotlin-compose-training-change-app-icon#0
 *      https://romannurik.github.io/AndroidAssetStudio/
 * 6. Limitation on foreground service, The changes are following android version:
 *      https://developer.android.com/develop/background-work/services/fgs/changes
 *      https://developer.android.com/develop/background-work/services/fgs/service-types
 * 7. Qt - QAndroidIntent: click F1 orr
 *      https://doc.qt.io/qt-6.5/qandroidintent.html
 * 8. Qt - Example app notification:
 *      https://doc.qt.io/qt-6.8/qtcore-platform-androidnotifier-example.html
 *
 * ============================================================================
 *
 * A. Deploy
 *  Before enable foreground service, first Qt project need and some android
 *  template files:
 *      - Default template path: ~/Qt/<version>/android_<abi>/src/android/templates
 *      - Sometimes this folder include: res/, AndroidManifest.xml, build.gradle
 *      - Now Create folder `android` in working project directory.
 *      - Copy 3 things in template folder above in to `android`
 *      - Now at QtCreator, in CMakeLists.txt, add `android` folder into project
 *
 *          (1) ( from Qt Reference [Deploy applications on android] )
 *          set_property(TARGET target_name PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
 *              "${CMAKE_CURRENT_SOURCE_DIR}/android")
 *
 *          (2) (Recommend)
 *          vv this `Hint command` below can see in default CMakeLists.txt file was
 *          generated when create project.
 *
 *          set_property(TARGET foreground_sv_test APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
 *              ${CMAKE_CURRENT_SOURCE_DIR}/android)
 *
 *  After above steps, if `android` folder not exist in project viewer,
 *      then right click on project and `Add Existing Directory...`,
 *      select `android` folder.
 *
 *  B. Some notes about folder `android/`:
 *  - res/values/libs.xml:
 *      (from QT - do no modified) It is used purely to manage deployment
 *      information of the Qt libraries, and it's not recommended to be manually modified.
 *  - AndroidManifest.xml:
 *      1.  This information is used to customize your application, it's used by the device
 *          to decide which features to enable
 *      2. The Android Manifest is also used to define Android Services and
 *          custom Android Activities.
 *  - build.gradle:
 *      is used to build Android packages.
 *      Not recommend to modify, just copy at right Qt version template.
 *
 *  - src/
 *      include any Java/Kotlin code to target some APIs that Qt doesn't cover or
 *      for some other reason. It necessary while create an andoid foreground service below.
 *
 * =====================================================================================
 *
 * A. Application Icon display on Launcher
 *  - See the reference [Create, add app icon on launcher]
 *      from `https://roman...`, upload image the it will generate a set of
 *      `mipmap-...` folder
 *  - copy all `mipmap-...` folder into `android/res/`, those are a set of icon
 *      help android adapts with any screen dpi's
 *  - Last one append this command in manifest:
 *      <application android:icon="@mipmap/file_icon_name" >
 *
 * B. Service in same process.
 *  In this example we focus run service in same process with
 *
 *  - Create `android/src/` folder to save Java code.
 *      - in QtCreator, right click then `add New...` -> `Java`
 *      - see [Qt Android services], the java code copied in `android/src/QtAndroidService.java`
 *          - file Java name must same name with class inside,
 *              otherwise Qt will raise an issues, build fail.
 *  - Now in CMakeList.txt
 *      find_package(Qt6 REQUIRED COMPONENTS Core)
 *      target_link_libraries(mytarget PRIVATE Qt6::CorePrivate)
 *  - In C++ source code:
 *      #include <QtCore/private/qandroidextras_p.h>
 *  - Then copy some example C++ call java though JNI like below.
 *      - it using #if defined(Q_OS_ANDROID) and #include <QtSystemDetection>
 *          to manage implement right android code.
 *      - Note that now `QtAndroidService.java` put at `android/src/QtAndroidService.java`
 *          - change example from Qt:
 *              QAndroidIntent serviceIntent(activity.object(),
 *                  "org/qtproject/example/qtandroidservice/QtAndroidService");
 *
 *              -- into -->
 *              QAndroidIntent serviceIntent(activity.object(),
 *                  "QtAndroidService");
 *  - Last one, in `android/AndroidManifest.xml`
 *      - a <service> tag with content must add inside tag <application>
 */


#include "mainwindow.h"

#include <QApplication>

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

#include "btnpushservice.h"

#include <QPushButton>
#include "notificationclient.h"

#include <QHBoxLayout>
#include <QWidget>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

// // [WARN] it doesn't work
// #if defined(Q_OS_ANDROID)
//     auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());
//     QAndroidIntent serviceIntent(activity.object(),
//                                 "QtAndroidService");
//     QJniObject result = activity.callObjectMethod(
//         "startService",
//         "(Landroid/content/Intent;)Landroid/content/ComponentName;",
//         serviceIntent.handle().object());
// #endif

    QWidget* wget_custom_center = new QWidget();
    QHBoxLayout* hbox_btn = new QHBoxLayout();

    wget_custom_center->setLayout(hbox_btn);
    w.setCentralWidget(wget_custom_center);


    BtnPushService* btn_start_service = new BtnPushService();
    btn_start_service->setText("Start service !!");

    QPushButton* btn_start_happy_notification = new QPushButton();
    QPushButton* btn_start_sad_notification = new QPushButton();

    btn_start_happy_notification->setText("Happy notification !!");
    btn_start_sad_notification->setText("Sad notification !!");

    hbox_btn->addWidget(btn_start_service);
    hbox_btn->addWidget(btn_start_happy_notification);
    hbox_btn->addWidget(btn_start_sad_notification);


    // connect
    NotificationClient* notify_worker = new NotificationClient();
    notify_worker->setParent(&w);

    QWidget::connect(btn_start_happy_notification, SIGNAL(clicked()), notify_worker, SLOT(setNotificationHappy()));
    QWidget::connect(btn_start_sad_notification, SIGNAL(clicked()), notify_worker, SLOT(setNotificationSad()));

    w.show();
    return a.exec();
}
