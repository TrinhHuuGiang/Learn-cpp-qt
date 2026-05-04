- why using QPixmap: available painting bitmap image, fast render 
    + Optimize for renderer like GPU (or CPU if fallback)
    + Optimize data keep in VRAM
    + Paint by QPainter

- why not QImage: 
    + (slow) need image processing on pixel (edit, filter) from CPU
    + (trivial) data keep in RAM
    + Paint by QPainter

- why not QIcon: need generate mutiple size before use
    + is a container of QPixmap with multiple sizes

- See more at: [_18_Painter](./_18_Painter.md)