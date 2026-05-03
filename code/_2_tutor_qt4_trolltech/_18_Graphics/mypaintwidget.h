#ifndef MYPAINTWIDGET_H
#define MYPAINTWIDGET_H

#include <QWidget>

#include <cstdint>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyPaintWidget;
}
QT_END_NAMESPACE

class MyPaintWidget : public QWidget
{
    Q_OBJECT

public:
    MyPaintWidget(QWidget *parent = nullptr);
    ~MyPaintWidget();

    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MyPaintWidget *ui;

    std::uint32_t repaint_count = 0;

};
#endif // MYPAINTWIDGET_H
