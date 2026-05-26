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
 *
 */


#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
