cmake_minimum_required(VERSION 3.16)

project(foreground_sv_test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets
    Core # need for android JNI
    )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets
    Core
    )

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(foreground_sv_test
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        android/gradle/wrapper/gradle-wrapper.jar android/gradle/wrapper/gradle-wrapper.properties android/res/mipmap-anydpi-v26/sunset.xml android/res/mipmap-hdpi/sunset.png android/res/mipmap-hdpi/sunset_adaptive_back.png android/res/mipmap-hdpi/sunset_adaptive_fore.png android/res/mipmap-mdpi/sunset.png android/res/mipmap-mdpi/sunset_adaptive_back.png android/res/mipmap-mdpi/sunset_adaptive_fore.png android/res/mipmap-xhdpi/sunset.png android/res/mipmap-xhdpi/sunset_adaptive_back.png android/res/mipmap-xhdpi/sunset_adaptive_fore.png android/res/mipmap-xxhdpi/sunset.png android/res/mipmap-xxhdpi/sunset_adaptive_back.png android/res/mipmap-xxhdpi/sunset_adaptive_fore.png android/res/mipmap-xxxhdpi/sunset.png android/res/mipmap-xxxhdpi/sunset_adaptive_back.png android/res/mipmap-xxxhdpi/sunset_adaptive_fore.png android/res/values/libs.xml android/AndroidManifest.xml android/build.gradle android/gradle.properties android/gradlew android/gradlew.bat
        android/src/QtAndroidService.java
        btnpushservice.h btnpushservice.cpp
        android/src/NotificationClient.java
        notificationclient.h notificationclient.cpp


    )

    if(ANDROID)
        set_property(TARGET foreground_sv_test APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/android)
    endif()

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET foreground_sv_test APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(foreground_sv_test SHARED
            ${PROJECT_SOURCES}
        )

# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(foreground_sv_test
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(foreground_sv_test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                    Qt6::CorePrivate # need for android JNI
                    )

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.foreground_sv_test)
endif()
set_target_properties(foreground_sv_test PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS foreground_sv_test
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(foreground_sv_test)
endif()
