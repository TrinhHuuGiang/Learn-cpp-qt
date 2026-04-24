/**
 * Include test:
 * - 01: Hello Qt
 * - 02: Connection signal-slot
 * - 03: Layout the widgets
 */

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>

int main(int argc, char *argv[])
{

    // Test 01: Hello Qt
    // QApplication app(argc, argv);
    // QLabel *label = new QLabel("<h2><i>Hello</i> "
    //                            "<font color=red>Qt!</font></h2>");
    // label->show();
    // return app.exec();



    // Test 02: Connection signal-slot
    // QApplication app(argc, argv);
    // QPushButton *button = new QPushButton("Quit");
    // QObject::connect(button, SIGNAL(clicked()),
    //                     &app, SLOT(quit()));
    // button->show();
    // return app.exec();



    // Test 03: layout the widgets
    QApplication app(argc, argv);

    QWidget *window = new QWidget;
    window->setWindowTitle("Enter Your Age");

    QSpinBox *spinBox = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Horizontal);

    spinBox->setRange(0, 100);
    slider->setRange(0, 130);

    QObject::connect(spinBox, SIGNAL(valueChanged(int)),
                         slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)),
                         spinBox, SLOT(setValue(int)));
    spinBox->setValue(35);

    // QHBoxLayout *layout = new QHBoxLayout;
    // layout->addWidget(spinBox);
    // layout->addWidget(slider);


    // QVBoxLayout *layout = new QVBoxLayout;
    // layout->addWidget(spinBox);
    // layout->addWidget(slider);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(spinBox,1,2);
    layout->addWidget(slider,2,3);

    window->setLayout(layout);
    window->show();

    return app.exec();
}
