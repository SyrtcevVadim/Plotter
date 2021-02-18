#include "plotter.h"
#include<QtWidgets>

Plotter::Plotter(QPoint *position, QSize *size, QWidget *parent): QWidget(parent)
{
    int w = size->width();
    int h = size->height();

    setCursor(Qt::CrossCursor);
    resize(w,h);
    move(position->x(), position->y());

    origin.setX(w/2);
    origin.setY(h/2);

    setGridCellWidth(10);
    setOriginWidth(3);
    setAxesWidth(1);
    setSingleTick(2);
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

void Plotter:: setSingleTick(int cells)
{
    singleTick = cells;
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

    drawAxesNames(&painter, QString("X"), QString("Y"));
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
    painter -> drawPoint(origin);

    painter -> drawText(origin.x()-gridCellWidth*0.75, origin.y()+gridCellWidth, QString("0"));
}

// Отрисовывает оси координат и засечки через каждый единичный отрезок
void Plotter:: drawAxes(QPainter *painter)
{
    QPen pen(Qt:: black, axesWidth);
    painter ->setPen(pen);

    // Отрисовываем оси координат
    painter ->drawLine(origin.x(), 0, origin.x(), height());
    painter ->drawLine(0, origin.y(), width(), origin.y());


    // Изображаем единичные засечки
    // Засечки на горизонтальной оси
    // В направлении положительных координат
    for(int xcoord = origin.x()+gridCellWidth*singleTick; xcoord <= width(); xcoord += gridCellWidth*singleTick)
    {
        QPoint bottomPoint(xcoord, origin.y() + gridCellWidth / 3);
        QPoint topPoint(xcoord, origin.y() - gridCellWidth / 3);
        painter -> drawLine(bottomPoint, topPoint);
    }
    // В направлении отрицательных координат
    for(int xcoord = origin.x()-gridCellWidth*singleTick; xcoord > 0; xcoord -= gridCellWidth*singleTick)
    {

        QPoint bottomPoint(xcoord, origin.y() + gridCellWidth / 3);
        QPoint topPoint(xcoord, origin.y() - gridCellWidth / 3);
        painter -> drawLine(bottomPoint, topPoint);
    }


    // Засечки на вертикальной оси
    //  В направлении положительных координат
    for(int ycoord = origin.y() - gridCellWidth*singleTick; ycoord >0; ycoord -= gridCellWidth*singleTick)
    {
        QPoint leftPoint(origin.x() - gridCellWidth/3, ycoord);
        QPoint rightPoint(origin.x() + gridCellWidth/3, ycoord);
        painter -> drawLine(leftPoint, rightPoint);
    }

    // В направлении отрицательных координат
    for(int ycoord = origin.y() + gridCellWidth*singleTick; ycoord <= height(); ycoord += gridCellWidth*singleTick)
    {
        QPoint leftPoint(origin.x() - gridCellWidth/3, ycoord);
        QPoint rightPoint(origin.x() + gridCellWidth/3, ycoord);
        painter -> drawLine(leftPoint, rightPoint);
    }

    // Отрисовываем стрелки, показывающие положительное направление на осях координат
    painter ->drawLine(width(), origin.y(), width()-gridCellWidth, origin.y()+gridCellWidth/2);
    painter ->drawLine(width(), origin.y(), width()-gridCellWidth, origin.y()-gridCellWidth/2);

    painter ->drawLine(origin.x(), 0, origin.x()+gridCellWidth/2, gridCellWidth);
    painter ->drawLine(origin.x(), 0, origin.x()-gridCellWidth/2, gridCellWidth);
}

// Отрисовывает названия осей координат
void Plotter::drawAxesNames(QPainter *painter, QString hAxeName, QString vAxeName)
{
    QPen pen(Qt::black, 2);
    painter ->setPen(pen);

    // Название горизонтальной оси
    painter->drawText(width()-gridCellWidth+2, origin.y()+gridCellWidth*2, hAxeName);
    // Название вертикальной оси

    painter ->drawText(origin.x() + gridCellWidth+2, 0 + gridCellWidth+2, vAxeName);
}
