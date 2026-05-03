#include "mypaintwidget.h"
#include "ui_mypaintwidget.h"


#include <QPainter>

    // Test when resize did Qt repaint?
#include <QDebug>


MyPaintWidget::MyPaintWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyPaintWidget)
{
    ui->setupUi(this);



}

MyPaintWidget::~MyPaintWidget()
{
    delete ui;
}


void MyPaintWidget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(80, 80, 400, 240);

    // Debug repaint count
        // show that when resize screen -> raise paintEvent
    ++repaint_count;
    qDebug()<<"Repaint cnt ["<<repaint_count<<"]";

}
