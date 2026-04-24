## Content
- [Layout application widgets](#layout-application-widgets)
    - Put QSlider and QPibBox into QHBoxLayout layout.
    - Put layout above into QWidget container.
    - Parent-child relationship:
        ``` txt
            Container Widget
            ( 
                Layout 
                (
                    UI Widget
                )
            )
        ```
    - Set window title by QWidget container.
- [Risk of infinite loop when using signal-slot](#risk-of-infinite-loop-when-using-signal-slot)


## What news:
- widget:
    - QSlider:  method setRange(), signal valueChanged(), slot setValue()
    - QSpinBox: method setRange(), signal valueChanged(), slot setValue()
- widget container (need a widget layout):
    - QWidget:  method setWindowTitle(), setLayout()
    - Others: QMainWindow, QDialog
- widget layout (it is widgets layout, not a widget, can't show):
    - QHBoxLayout:  method addWidget()
    - Others: QVBoxLayout, QGridLayout

## Layout application widgets
```cpp
    001 #include <QApplication>
    002 #include <QHBoxLayout>
    003 #include <QSlider>
    004 #include <QSpinBox>
    005 int main(int argc, char *argv[])
    006 {

    007 QApplication app(argc, argv);

    008 QWidget *window = new QWidget;
    009 window->setWindowTitle("Enter Your Age");

    010 QSpinBox *spinBox = new QSpinBox;
    011 QSlider *slider = new QSlider(Qt::Horizontal);

    012 spinBox->setRange(0, 130);
    013 slider->setRange(0, 130);

    014 QObject::connect(spinBox, SIGNAL(valueChanged(int)),
    015 slider, SLOT(setValue(int)));
    016 QObject::connect(slider, SIGNAL(valueChanged(int)),
    017 spinBox, SLOT(setValue(int)));
    018 spinBox->setValue(35);

    019 QHBoxLayout *layout = new QHBoxLayout;
    020 layout->addWidget(spinBox);
    021 layout->addWidget(slider);

    022 window->setLayout(layout);
    023 window->show();

    024 return app.exec();
    025 }
```


## Risk of infinite loop when using signal-slot

Example, at **018**:
- After setup connection between `QSpinBox` with `QSlider`:
    - *spinBox* set value to 35
    will emit `valueChanged()` signal, make *slider* `setValue()` slot update 
    slide bar value to 35.
    - Then *slider* continue emit it `valueChanged()` signal to *spinBox*
    `setValue()` slot.

- The risk of infinite loop appear now, but it now prevents by simple compare
value inside `setValue()` slot. Anytime value no change, emit is refused.
