#include "widget.h"
#include "ui_widget.h"


void Widget::drawCoordinateSystem(QPainter *painter)
{
    drawGrid(painter);
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter->drawLine(-10000 + offset.x(), 0 + offset.y(), 10000 + offset.x(), 0 + offset.y()); // Горизонтальная ось
    painter->drawLine(0 + offset.x(), -10000 + offset.y(), 0 + offset.x(), 10000 + offset.y()); // Вертикальная ось
}

void Widget::drawGrid(QPainter *painter) {
    painter->setPen(QPen(Qt::lightGray, 1, Qt::DotLine));

    int step = 50;
    int w = 10000;
    int h = 10000;

    for (int x = -w; x <= w; x += step) {
        painter->drawLine(x + offset.x(), -h + offset.y(), x + offset.x(), h + offset.y());
    }

    for (int y = -h; y <= h; y += step) {
        painter->drawLine(-w + offset.x(), y + offset.y(), w + offset.x(), y + offset.y());
    }
}
