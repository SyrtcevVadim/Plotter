#include "GUI/paintingarea.h"
#include "LibForPlotter/graph.h"
#include<QtWidgets>

PaintingArea::PaintingArea(const QSize &size, QWidget *parentWidget): QWidget(parentWidget)
{
    setAcceptDrops(true);
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setCursor(Qt::CrossCursor);

    areaWidth = size.width();
    areaHeight = size.height();
    leftIndent=20.0;
    bottomIndent=20.0;

    resize(areaWidth+leftIndent, areaHeight+bottomIndent);
    moveOriginPoint(QPointF(width()/2, (areaHeight)/2));
    setOriginPointThickness(5.0);
    setAxesThickness(0.5);
    setGridLineThickness(0.5);
    setBorderThickness(2.5);
    setGridCellWidth(10.0);
    setGraphThickness(3.0);
    setUnitSegmentValue(5);
    setUnitSegmentCellQuantity(5);

}

void PaintingArea::setUnitSegmentValue(double value)
{
    unitSegmentValue = value;
}

void PaintingArea::setUnitSegmentCellQuantity(int cellQuantity)
{
    cellQuantityInUnitSegment = cellQuantity;
}

void PaintingArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Draws the painting area
    drawGrid(painter);
    drawOriginPoint(painter);
    drawAxes(painter);
    drawCoordinates(painter);
    drawAxesNames(painter);

    for(Graph *item: graphs)
    {
        double step{item->getSingleStep()};
        for(double x{item->getMin()+step}; x < item->getMax(); x++)
        {
            if(((*item)[x-step] != qInf()) &&
               ((*item)[x-step] == (*item)[x-step])&&
               ((*item)[x] != qInf()) &&
               ((*item)[x] == (*item)[x]))
            {
                drawLineF(painter, QPointF(x-step, (*item)[x-step]), QPointF(x, (*item)[x]), item->getColor());
            }
        }
    }
    /*
    // Tests for drawing points
    drawPointF(painter, QPointF(3, 5), Qt::blue);
    drawPointF(painter, QPointF(4, 6), Qt::red);
    drawPointF(painter, QPointF(-7.5, -11), Qt::darkMagenta);

    // Tests for drawing lines
    drawLineF(painter, QPointF(-1,1),QPointF(7,15.3), Qt::darkRed);
    drawLineF(painter, QPointF(-7,7), QPointF(11.3,15.4), Qt::darkGreen);
    */
}

void PaintingArea::setOriginPointThickness(double value)
{
    originPointThickness = value;
}

void PaintingArea::setAxesThickness(double value)
{
    axesThickness = value;
}

void PaintingArea::setGridLineThickness(double value)
{
    gridLineThickness=value;
}

void PaintingArea::setBorderThickness(double value)
{
    borderThickness = value;
}

void PaintingArea::setGridCellWidth(double width)
{
    gridCellWidth = width;
}

void PaintingArea::setGraphThickness(double value)
{
    graphThickness = value;
}

void PaintingArea::moveOriginPoint(const QPointF &pos)
{
    originPoint = pos;
}

void PaintingArea::drawOriginPoint(QPainter &painter)
{
    QPen pen(Qt::black, originPointThickness);
    painter.setPen(pen);
    painter.drawPoint(originPoint);
}

void PaintingArea::drawGrid(QPainter &painter)
{
    QPen pen(Qt::lightGray, gridLineThickness);
    painter.setPen(pen);

    // Draws horizontal lines from origin point in positive direction
    for(double y{originPoint.y()}; y >= 0; y-=gridCellWidth)
    {
        painter.drawLine(QPoint(leftIndent, y), QPoint(areaWidth+leftIndent, y));
    }
    // Draws horizontal lines from origin point in negative direction
    for(double y{originPoint.y()-gridCellWidth}; y <= areaHeight; y+=gridCellWidth)
    {
        painter.drawLine(QPoint(leftIndent, y), QPoint(leftIndent+areaWidth, y));
    }

    // Draws vertical lines from origin point in positive direction
    for(double x{originPoint.x()}; x <= areaWidth+leftIndent; x+=gridCellWidth)
    {
        painter.drawLine(QPoint(x, 0), QPoint(x, areaHeight));
    }
    // Draws vertical lines from origin point in negative direction
    for(double x{originPoint.x()-gridCellWidth}; x >= leftIndent; x-=gridCellWidth)
    {
        painter.drawLine(QPoint(x, 0), QPoint(x, areaHeight));
    }
}

void PaintingArea::drawAxes(QPainter &painter)
{
    QPen pen(Qt::black, axesThickness);
    painter.setPen(pen);

    // Draws vertical coordinate axe
    painter.drawLine(QPoint(originPoint.x(),0), QPoint(originPoint.x(), areaHeight));
    // Draw vertical axe's arrow
    painter.drawLine(QPoint(originPoint.x(),0),
                     QPoint(originPoint.x()-gridCellWidth/2, gridCellWidth));
    painter.drawLine(QPoint(originPoint.x(), 0),
                     QPoint(originPoint.x()+gridCellWidth/2, gridCellWidth));

    // Draws horizontal coordinate axe
    painter.drawLine(QPoint(leftIndent, originPoint.y()), QPoint(areaWidth+leftIndent, originPoint.y()));
    // Draw horizontal axe's arrow
    painter.drawLine(QPoint(areaWidth+leftIndent-gridCellWidth, originPoint.y()+gridCellWidth/2),
                     QPoint(areaWidth+leftIndent, originPoint.y()));
    painter.drawLine(QPoint(areaWidth+leftIndent-gridCellWidth, originPoint.y()-gridCellWidth/2),
                     QPoint(areaWidth+leftIndent, originPoint.y()));
}

void PaintingArea::drawAxesNames(QPainter &painter)
{
    QPen pen(Qt::black);
    painter.setPen(pen);

    // Draws OX axes name
    painter.drawText(areaWidth+leftIndent-7, originPoint.y()+15, "X");
    // Draws OY axes name
    painter.drawText(originPoint.x()+7, 10, "Y");

}

void PaintingArea::drawCoordinates(QPainter &painter)
{
    QPen pen(Qt::black);
    painter.setPen(pen);

    double currentValue{0.0};

    // Draws serifs after every unit segment on vertical axe
    // From origin point in positive direction
    for(double y{originPoint.y()}; y >= gridCellWidth*cellQuantityInUnitSegment; y-=gridCellWidth*cellQuantityInUnitSegment)
    {
        painter.drawLine(QPoint(originPoint.x()-3, y), QPoint(originPoint.x()+3, y));
        painter.drawText(0, y+4, QString().setNum(currentValue));
        currentValue+= unitSegmentValue;
    }
    currentValue = -unitSegmentValue;
    // From origin point in negative direction
    for(double y{originPoint.y()+gridCellWidth*cellQuantityInUnitSegment}; y <= areaHeight; y+= gridCellWidth*cellQuantityInUnitSegment)
    {
        painter.drawLine(QPoint(originPoint.x()-3, y), QPoint(originPoint.x()+3, y));
        painter.drawText(0, y+4, QString().setNum(currentValue));
        currentValue -= unitSegmentValue;
    }

    currentValue = 0.0;
    // Draws serifs after every unit segment on horizontal axe
    // From origin point in positive direction
    for(double x{originPoint.x()}; x < areaWidth+leftIndent - gridCellWidth*cellQuantityInUnitSegment; x+=gridCellWidth*cellQuantityInUnitSegment)
    {
        painter.drawLine(QPoint(x, originPoint.y()+3), QPoint(x, originPoint.y()-3));
        painter.drawText(x-3, areaHeight+12,QString().setNum(currentValue));
        currentValue += unitSegmentValue;
    }
    currentValue = -unitSegmentValue;
    // From origin point in negative direction
    for(double x{originPoint.x()-gridCellWidth*cellQuantityInUnitSegment}; x >= leftIndent; x-= gridCellWidth*cellQuantityInUnitSegment)
    {
        painter.drawLine(QPoint(x, originPoint.y()+3), QPoint(x, originPoint.y()-3));
        painter.drawText(x-7, areaHeight+12,QString().setNum(currentValue));
        currentValue -= unitSegmentValue;
    }
}

void PaintingArea::drawPointF(QPainter &painter, const QPointF &point, const QColor &color)
{
    QPen pen(color, graphThickness);
    painter.setPen(pen);

    painter.drawPoint(fromPaintingAreaToWidget(point));
}

void PaintingArea::drawLineF(QPainter &painter, const QPointF &firstPoint, const QPointF &secondPoint, const QColor &color)
{
    QPen pen(color, graphThickness);
    painter.setPen(pen);

    painter.drawLine(fromPaintingAreaToWidget(firstPoint), fromPaintingAreaToWidget(secondPoint));
}

QPointF PaintingArea::fromWidgetToPaintingArea(const QPointF &coord)
{
    double x = coord.x();
    double y = coord.y();
    return QPointF(((x-originPoint.x())*unitSegmentValue)/(gridCellWidth*cellQuantityInUnitSegment),
                   ((originPoint.y()-y)*unitSegmentValue)/(gridCellWidth*cellQuantityInUnitSegment));
}

QPointF PaintingArea::fromPaintingAreaToWidget(const QPointF &coord)
{
    double x = coord.x();
    double y = coord.y();
    return QPointF(originPoint.x()+x*gridCellWidth*cellQuantityInUnitSegment/unitSegmentValue,
                   originPoint.y()-y*gridCellWidth*cellQuantityInUnitSegment/unitSegmentValue);
}

void PaintingArea::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "Мышь движется по виджету!";
    qDebug() << fromWidgetToPaintingArea(event->pos());
}

QSize PaintingArea::sizeHint() const
{
    return QSize(areaWidth+leftIndent, areaHeight+bottomIndent);
}

void PaintingArea::addFunction(MathExpression *function)
{
    qDebug() << "Added new function: " << *function;
    Graph *newGraph = new Graph(function);
    graphs.append(newGraph);
}

void PaintingArea::changeGraphColor(MathExpression *function, QColor color)
{
    qDebug() << "Color of " << *function << " is changed!";
    for(Graph *item: graphs)
    {
        if(item->getExpression() == function)
        {
            item->setColor(color);
            if(item->isDrawn())
            {
                repaint();
            }
        }
    }
}

void PaintingArea::removeGraph(MathExpression *function)
{
    qDebug() << *function << " is deleted!";
    for(Graph *item: graphs)
    {
        if(item->getExpression() == function)
        {
            graphs.removeOne(item);
            delete item;
            break;
        }
    }
    repaint();
}

void PaintingArea::changeGraph(MathExpression *function)
{
    qDebug() << *function << " is changed! Recalculating of table of values";
    for(Graph *item: graphs)
    {
        if(item->getExpression() == function)
        {
            item->recalculate();
            if(item->isDrawn())
            {
                repaint();
            }
            break;
        }
    }
}

void PaintingArea::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "DRAG ENTER EVENT!";
    if(event->mimeData()->hasFormat("MathExpression"))
    {
        event->acceptProposedAction();
    }
}

void PaintingArea::dropEvent(QDropEvent *event)
{
    qDebug() << "DROP EVENT";
    QByteArray byteArray(event->mimeData()->data("MathExpression"));
    QDataStream in(&byteArray, QIODevice::ReadOnly);

    MathExpression expression;
    in >> expression;
    qDebug() <<"Dropped expression: "<< expression;

    for(Graph *item: graphs)
    {
        qDebug() << "current expression: " << *item->getExpression();
        if(item->getExpression()->GetInfixExpression() == expression.GetInfixExpression())
        {
            item->setDrawn();
        }
    }
    repaint();
}
