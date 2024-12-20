#include "widget.h"
#include "ui_widget.h"


void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastMousePos = event->pos();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        QPoint delta = event->pos() - lastMousePos;

        offset += delta;

        lastMousePos = event->pos();

        update();
    }
}
