#ifndef ANIMATION_WIDGET_H
#define ANIMATION_WIDGET_H

#include <QWidget>

class animation_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit animation_Widget(QWidget *parent = nullptr);

public slots:
    void onTick();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double t;
    bool forward;
};

#endif // ANIMATION_WIDGET_H
