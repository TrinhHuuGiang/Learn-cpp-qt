#ifndef ICONEDITOR_H
#define ICONEDITOR_H

#include <QWidget>

#include <QColor>
#include <QImage>

class IconEditor : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    explicit IconEditor(QWidget *parent = nullptr);
    ~IconEditor();

// Setter and getter
    void setPenColor(const QColor &newColor);
    QColor penColor() const { return curColor; }

        // retrieve icon, save to file
    void setIconImage(const QImage &newImage);
        // when open icon file
    QImage iconImage() const { return image; }

    void setZoomFactor(int newZoom);
    int zoomFactor() const { return zoom; }

    QSize sizeHint() const;

protected:

// virtual from `QWidget`
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    void setImagePixel(const QPoint &pos, bool opaque);
    QRect pixelRect(int i, int j) const;

private:

    QColor curColor;
        // init with 16x16 pixel,
        // 32-bit ARGB(alpha_8b,red_8b,green_8b,blue_8b)
            // format that supports semi-transparency

    QImage image;
    int zoom;

};

#endif // ICONEDITOR_H
