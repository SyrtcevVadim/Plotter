#include "plotter.h"
#include<QtWidgets>

Plotter::Plotter(QPoint *position, QSize *size, QWidget *parent): QWidget(parent)
{
    int w = size->width();
    int h = size->height();

    setCursor(Qt::CrossCursor);
    resize(w,h);
    move(position->x(), position->y());

    origin = new QPoint(w/2, h/2);


    setGridCellWidth(10);
    setOriginWidth(3);
    setAxesWidth(1);
    setUnitSegmentCells(1);

}

// Устанавливает длину стороны ячейки сетки
void Plotter::setGridCellWidth(int width)
{
    gridCellWidth = width;
}

// Устанавливает толщину точки начала координат
void Plotter::setOriginWidth(int width)
{
    originWidth = width;
}

void Plotter:: setUnitSegmentCells(int cells)
{
    unitSegment = cells;
}

// Устанавливает толщину линий осей координат
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

// Отрисовывает сетку для графостроителя
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

// Отрисовывает начало координат
void Plotter::drawOrigin(QPainter *painter)
{
    QPen pen(Qt:: black, originWidth);
    painter ->setPen(pen);
    painter -> drawPoint(origin->x(), origin ->y());

}

// Отрисовывает оси координат и засечки через каждый единичный отрезок
void Plotter:: drawAxes(QPainter *painter)
{
    QPen pen(Qt:: black, axesWidth);
    painter ->setPen(pen);

    // Отрисовываем оси координат
    painter ->drawLine(origin -> x(), 0, origin -> x(), height());
    painter ->drawLine(0, origin -> y(), width(), origin -> y());

    // Изображаем единичные засечки
    // Засечки на горизонтальной оси
    for(int x = gridCellWidth; x <= width(); x += gridCellWidth*unitSegment)
    {
        QPoint bottomPoint(x, origin -> y() + gridCellWidth / 3);
        QPoint topPoint(x, origin -> y() - gridCellWidth / 3);
        painter -> drawLine(bottomPoint, topPoint);
    }

    for(int y = gridCellWidth; y <=height(); y += gridCellWidth*unitSegment)
    {
        QPoint leftPoint(origin -> x() - gridCellWidth/3, y);
        QPoint rightPoint(origin -> x() + gridCellWidth/3, y);
        painter -> drawLine(leftPoint, rightPoint);
    }

}
