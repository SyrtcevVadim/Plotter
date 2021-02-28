#include "plotter.h"
#include<QtWidgets>

Plotter::Plotter(QPoint *position /*=0*/, QSize *size, QWidget *parent): QWidget(parent)
{
    int w = size->width();
    int h = size->height();

    setCursor(Qt::CrossCursor);
    resize(w,h);
    move(position->x(), position->y());

    origin.setX(w/2);
    origin.setY(h/2);

    setGridCellWidth(10);
    setOriginWidth(5);
    setAxesWidth(0.5);
    setSingleTick(2);
}

void Plotter::paintEvent(QPaintEvent *event)
{
    // Не используем параметр event
    Q_UNUSED(event);

    // Данный объект занимается отрисовкой всей графики
    QPainter painter(this);

    drawGrid(&painter);
    drawOrigin(&painter);
    drawAxes(&painter);

    drawAxesNames(&painter, QString("X"), QString("Y"));

    // Тестируем отрисовку точек
    /*
    for(int i = -10; i <= 10; i++)
    {
        drawPoint(&painter, QPoint(i, i));
    }

    for(double i = -10.0; i <= 10.0; i+=0.01)
    {
        drawPointF(&painter, QPointF(i, -i));
    }
    */
    // Тестируем отрисовку линий

    drawLineF(&painter, QPointF(-3.0, 3.0), QPointF(3.0, 3.0), Qt::darkRed);
    drawLineF(&painter, QPointF(-5.0, -5.0), QPointF(1.0, 1.0), Qt::darkYellow);

}

void Plotter::setGridCellWidth(int width)
{
    gridCellWidth = width;
}

void Plotter::setOriginWidth(double width)
{
    originWidth = width;
}

void Plotter:: setSingleTick(int cells)
{
    singleTick = cells;
}

void Plotter::setAxesWidth(double width)
{
    axesWidth = width;
}

void Plotter::drawGrid(QPainter *painter)
{
    QPen pen(Qt::gray, .3);
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

    painter -> drawPoint(origin);
    painter -> drawText(origin.x()-gridCellWidth*0.75, origin.y()+gridCellWidth, QString("0"));
}

void Plotter:: drawAxes(QPainter *painter)
{
    QPen pen(Qt:: black, axesWidth);
    painter ->setPen(pen);

    // Отрисовываем вертикальную ось
    painter ->drawLine(origin.x(), 0, origin.x(), height());
    // Отрисовываем горизонтальную ось
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
    // На горизонтальных осях
    painter ->drawLine(width(), origin.y(), width()-gridCellWidth, origin.y()+gridCellWidth/2);
    painter ->drawLine(width(), origin.y(), width()-gridCellWidth, origin.y()-gridCellWidth/2);

    // На вертикальных осях
    painter ->drawLine(origin.x(), 0, origin.x()+gridCellWidth/2, gridCellWidth);
    painter ->drawLine(origin.x(), 0, origin.x()-gridCellWidth/2, gridCellWidth);
}

void Plotter::drawAxesNames(QPainter *painter, QString hAxeName, QString vAxeName)
{
    QPen pen(Qt::black, 2);
    painter ->setPen(pen);

    // Название горизонтальной оси
    painter->drawText(width()-gridCellWidth+2, origin.y()+gridCellWidth*2, hAxeName);

    // Название вертикальной оси
    painter ->drawText(origin.x() + gridCellWidth+2, 0 + gridCellWidth+2, vAxeName);
}

void Plotter::drawPoint(QPainter *painter, QPoint point, QColor color)
{
    QPen pen{color, 3};
    painter->setPen(pen);

    painter->drawPoint(origin.x()+(point.x()*gridCellWidth*singleTick), origin.y()-(point.y()*gridCellWidth*singleTick));
}

void Plotter::drawPointF(QPainter *painter, QPointF point, QColor color)
{
    QPen pen{color, 2};
    painter->setPen(pen);

    painter->drawPoint(origin.x()+(point.x()*gridCellWidth*singleTick), origin.y()-(point.y()*gridCellWidth*singleTick));

}

void Plotter::drawLineF(QPainter *painter, QPointF startPoint, QPointF endPoint, QColor color)
{
    QPen pen{color, 2};
    painter ->setPen(pen);

    painter->drawLine(origin.x() +(startPoint.x()*gridCellWidth*singleTick),
                      origin.y() - (startPoint.y()*gridCellWidth*singleTick),
                      origin.x() +(endPoint.x()*gridCellWidth*singleTick),
                      origin.y() - (endPoint.y()*gridCellWidth*singleTick));
}
