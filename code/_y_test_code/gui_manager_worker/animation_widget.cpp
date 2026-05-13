#include "animation_widget.h"

#include <QPainter>
#include <QtMath>

animation_Widget::animation_Widget(QWidget *parent)
    : QWidget{parent}
{
    t = 0.0;
    forward = true;

    setMinimumSize(400, 200);
}




void animation_Widget::onTick()
{
    double speed = 0.01;

    if (forward)
        t += speed;
    else
        t -= speed;

    if (t >= 1.0)
    {
        t = 1.0;
        forward = false;
    }
    else if (t <= 0.0)
    {
        t = 0.0;
        forward = true;
    }

    update(); // trigger repaint widget inqueue
}


void animation_Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.fillRect(rect(), Qt::black);

    QPointF A(width() * 0.1, height() * 0.5);
    QPointF B(width() * 0.8, height() * 0.5);

    QPointF pos = A * (1.0 - t) + B * t;

    // p.setBrush(Qt::red);
    // p.setPen(Qt::NoPen);
    // p.setPen(Qt::white);

    QPen pen(Qt::blue);
    pen.setWidth(3);
    p.setPen(pen);
    p.drawEllipse(pos, 15, 15);

    p.setPen(Qt::gray);
    p.drawLine(A, B);
}
