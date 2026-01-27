# tutorial-cpp-qt
This repository helps us quickly get familiar with Qt to write basic UI or console applications.

## Content
- [QT Console](./code/_0_code_console/)
    + slot & signal, parent & child
    + manage dynamic QObject life cycle
    + threading
    + mutex
- [QT Widget](./code/_1_code_widgets/)
    + state machine
    + widget
    + sqlite service (comming soon)
    + HTTP, MQTT

## Requirements
- QT Creator: `version 6.5` or another Qt6 versions
- I'm using the latest recommended JDK, SDK, NDK, etc., provided by Qt Creator for designing Widget UI applications, including:
    + Google USB Driver: 13
    + NDK: 25.1.8937393
    + Android emulator: 35.5.10
    + Android SDK platform-Tools: 35.0.2
    + Android SDK platform-Tools 33: 33.0.0
    + Android SDK command-line tools: latest
    + Android 13: SDK flatform (API 33)
    + Android 13 Google Play Intel x86_64 Atom System Image (API 33) <*Not recommended*> — this virtual device runs very slowly on my laptop :v
    + Android 8 : Google Play Intel x86_64 Atom System Image (API 26)  <**Recommend**>

## Reference
- Some ideas and techniques in this repository were inspired by the content from: [@VoidRealms](https://www.youtube.com/@VoidRealms)

## Note:
- Qt5.15 support api 21+ (Android 5+), https://www.qthub.com/static/doc/qt5/qtdoc/android.html#
- Qt6.5 support api 26+ (Android 8+), https://doc.qt.io/qt-6.5/supported-platforms.html
- Qt6.8 support api 28+ (Android 9+)