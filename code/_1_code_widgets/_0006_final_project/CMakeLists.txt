cmake_minimum_required(VERSION 3.16)

project(_0006_final_project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets
    Svg Mqtt Network Sql) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets
    Svg Mqtt Network Sql) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

set(PROJECT_SOURCES
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(_0006_final_project
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        rsc_f.qrc
        _1_menuconfig.h _1_menuconfig.cpp _1_menuconfig.ui
        z_widget_style.h
        z_widget_style.cpp
        _a_login_to_broker.h _a_login_to_broker.cpp _a_login_to_broker.ui
        _b_config_logic_layer.h _b_config_logic_layer.cpp _b_config_logic_layer.ui
        _c_update_mqtt_info.h _c_update_mqtt_info.cpp _c_update_mqtt_info.ui
        _d_update_wifi_info.h _d_update_wifi_info.cpp _d_update_wifi_info.ui
        rsrc_code/mqtt_topic/_002_B0_mqtt_topic.h
        rsrc_code/mqtt_topic/_001_B0_mqtt_topic.h
        z_global_db_connect.h
        z_global_db_connect.cpp
        rsrc_code/mqtt_topic/__general_handshake_topic.h
        _a_ltb_logic_block/_a_ltb_000_logic_base_ui.h _a_ltb_logic_block/_a_ltb_000_logic_base_ui.cpp
        _a_ltb_logic_block/_a_ltb_001_logic_base_map.h _a_ltb_logic_block/_a_ltb_001_logic_base_map.cpp
        _a_ltb_logic_block/_a_ltb_link_B0_DF_000_logic_bat_check.h _a_ltb_logic_block/_a_ltb_link_B0_DF_000_logic_bat_check.cpp
        _a_ltb_logic_block/_a_ltb_link_B0_DF_001_logic_au_test.h _a_ltb_logic_block/_a_ltb_link_B0_DF_001_logic_au_test.cpp
        rsrc_code/http_path/_http_path.h
        _b_config_logic_layer_2.h _b_config_logic_layer_2.cpp _b_config_logic_layer_2.ui

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET _0006_final_project APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

else()

    if(ANDROID) # Configure for Qt5 on Android
        find_package(Qt5 REQUIRED COMPONENTS AndroidExtras)

        # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
        set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android" CACHE INTERNAL "")

        add_library(_0006_final_project SHARED
                ${PROJECT_SOURCES}
            rsc_f.qrc
            _1_menuconfig.h _1_menuconfig.cpp _1_menuconfig.ui
            z_widget_style.h
            z_widget_style.cpp
            _a_login_to_broker.h _a_login_to_broker.cpp _a_login_to_broker.ui
            _b_config_logic_layer.h _b_config_logic_layer.cpp _b_config_logic_layer.ui
            _c_update_mqtt_info.h _c_update_mqtt_info.cpp _c_update_mqtt_info.ui
            _d_update_wifi_info.h _d_update_wifi_info.cpp _d_update_wifi_info.ui
            rsrc_code/mqtt_topic/_002_B0_mqtt_topic.h
            rsrc_code/mqtt_topic/_001_B0_mqtt_topic.h
            z_global_db_connect.h
            z_global_db_connect.cpp
            rsrc_code/mqtt_topic/__general_handshake_topic.h
            _a_ltb_logic_block/_a_ltb_000_logic_base_ui.h _a_ltb_logic_block/_a_ltb_000_logic_base_ui.cpp
            _a_ltb_logic_block/_a_ltb_001_logic_base_map.h _a_ltb_logic_block/_a_ltb_001_logic_base_map.cpp
            _a_ltb_logic_block/_a_ltb_link_B0_DF_000_logic_bat_check.h _a_ltb_logic_block/_a_ltb_link_B0_DF_000_logic_bat_check.cpp
            _a_ltb_logic_block/_a_ltb_link_B0_DF_001_logic_au_test.h _a_ltb_logic_block/_a_ltb_link_B0_DF_001_logic_au_test.cpp
            rsrc_code/http_path/_http_path.h
            _b_config_logic_layer_2.h _b_config_logic_layer_2.cpp _b_config_logic_layer_2.ui

        )

        target_link_libraries(_0006_final_project PRIVATE Qt5::AndroidExtras)
        # add_dependencies(apk _0006_final_project)


# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")

    else() # Configure for Qt5 on Window (executable = exe)
        add_executable(_0006_final_project
            ${PROJECT_SOURCES}
            rsc_f.qrc
            _1_menuconfig.h _1_menuconfig.cpp _1_menuconfig.ui
            z_widget_style.h
            z_widget_style.cpp
            _a_login_to_broker.h _a_login_to_broker.cpp _a_login_to_broker.ui
            _b_config_logic_layer.h _b_config_logic_layer.cpp _b_config_logic_layer.ui
            _c_update_mqtt_info.h _c_update_mqtt_info.cpp _c_update_mqtt_info.ui
            _d_update_wifi_info.h _d_update_wifi_info.cpp _d_update_wifi_info.ui
            rsrc_code/mqtt_topic/_002_B0_mqtt_topic.h
            rsrc_code/mqtt_topic/_001_B0_mqtt_topic.h
            z_global_db_connect.h
            z_global_db_connect.cpp
            rsrc_code/mqtt_topic/__general_handshake_topic.h
            _a_ltb_logic_block/_a_ltb_000_logic_base_ui.h _a_ltb_logic_block/_a_ltb_000_logic_base_ui.cpp
            _a_ltb_logic_block/_a_ltb_001_logic_base_map.h _a_ltb_logic_block/_a_ltb_001_logic_base_map.cpp
            _a_ltb_logic_block/_a_ltb_link_B0_DF_000_logic_bat_check.h _a_ltb_logic_block/_a_ltb_link_B0_DF_000_logic_bat_check.cpp
            _a_ltb_logic_block/_a_ltb_link_B0_DF_001_logic_au_test.h _a_ltb_logic_block/_a_ltb_link_B0_DF_001_logic_au_test.cpp
            rsrc_code/http_path/_http_path.h
            _b_config_logic_layer_2.h _b_config_logic_layer_2.cpp _b_config_logic_layer_2.ui


        )
    endif()
endif()

target_link_libraries(_0006_final_project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                        Qt${QT_VERSION_MAJOR}::Svg
                        Qt${QT_VERSION_MAJOR}::Mqtt
                        Qt${QT_VERSION_MAJOR}::Network
                        Qt${QT_VERSION_MAJOR}::Sql)#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


# Add library SSL 1.1 / 3 for android // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
# go to Edit -> Preferences... -> Devices -> android -> download openssl
# get this folder download then cope to this project folder
# else android will not use mqtts
# Note: these folder have file share object: libssl.so  libcrypto.so << i dont know why them can available
# Note: i use ssl 1.1  but android return
#       [The backend "cert-only" does not support QSslKey Qt android]

if(ANDROID)
    set_property(TARGET _0006_final_project PROPERTY QT_ANDROID_EXTRA_LIBS
        ${CMAKE_SOURCE_DIR}/rsrc_dir/android_openssl/ssl_3/armeabi-v7a/libssl_3.so
        ${CMAKE_SOURCE_DIR}/rsrc_dir/android_openssl/ssl_3/armeabi-v7a/libcrypto_3.so
        ${CMAKE_SOURCE_DIR}/rsrc_dir/android_openssl/ssl_3/arm64-v8a/libssl_3.so
        ${CMAKE_SOURCE_DIR}/rsrc_dir/android_openssl/ssl_3/arm64-v8a/libcrypto_3.so
        # ${CMAKE_SOURCE_DIR}/rsrc_dir/android_openssl/ssl_1.1/armeabi-v7a/libssl_1_1.so
        # ${CMAKE_SOURCE_DIR}/rsrc_dir/android_openssl/ssl_1.1/armeabi-v7a/libcrypto_1_1.so
        # ${CMAKE_SOURCE_DIR}/rsrc_dir/android_openssl/ssl_1.1/arm64-v8a/libssl_1_1.so
        # ${CMAKE_SOURCE_DIR}/rsrc_dir/android_openssl/ssl_1.1/arm64-v8a/libcrypto_1_1.so
    )
endif()




# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example._0006_final_project)
endif()
set_target_properties(_0006_final_project PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS _0006_final_project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(_0006_final_project)
endif()
