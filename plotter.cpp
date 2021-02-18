#include "plotter.h"
#include<QtWidgets>

Plotter::Plotter(QPoint *position, QSize *size, QWidget *parent): QWidget(parent)
{
    int w = size->width();
    int h = size->height();
    resize(w,h);
    move(position->x(), position->y());


    origin = new QPoint(w/2, h/2);


    setGridCellWidth(10);
    setOriginWidth(3);
    setAxesWidth(1);

}

void Plotter::setGridCellWidth(int width)
{
    gridCellWidth = width;
}

void Plotter::setOriginWidth(int width)
{
    originWidth = width;
}

void Plotter::setAxesWidth(int width)
{
    axesWidth = width;
}

void Plotter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    drawGrid(&painter);
    drawOrigin(&painter);
    drawAxes(&painter);


}

void Plotter::drawGrid(QPainter *painter)
{
    QPen pen(Qt::gray, 1);
    painter ->setPen(pen);

    // Отрисовываем вертикальные линии
    for(int x = gridCellWidth; x <= width(); x+= gridCellWidth)
    {
        painter -> drawLine(x, 0, x, height());
    }

    // Отрисовываем горизонтальные линии
    for(int y = gridCellWidth; y <= height(); y+= gridCellWidth)
    {
        painter -> drawLine(0, y,width(), y);
    }

}

void Plotter::drawOrigin(QPainter *painter)
{
    QPen pen(Qt:: black, originWidth);
    painter ->setPen(pen);
    painter -> drawPoint(origin->x(), origin ->y());

}

void Plotter:: drawAxes(QPainter *painter)
{
    QPen pen(Qt:: black, axesWidth);
    painter ->setPen(pen);

    painter ->drawLine(origin->x(), 0, origin->x(), height());
    painter ->drawLine(0, origin->y(), width(), origin->y());

}
