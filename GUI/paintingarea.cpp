#include "GUI/paintingarea.h"
#include "LibForPlotter/graph.h"
#include <QtWidgets>

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
    setGridCellWidth(12.0);
    setGraphThickness(1.5);
    setUnitSegmentValue(10);
    setUnitSegmentCellQuantity(5);

    // Adjusts the single step of a variable inside table of variables in dependence of the scale factor
    Graph::setSingleStep((unitSegmentValue*graphThickness)/(2*gridCellWidth*cellQuantityInUnitSegment));
    qDebug() << "Single step for current scale: " << Graph::getSingleStep();

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

    // Adjusts scale of painting area
    /*double maxAbsoluteValue;
    for(auto it{graphs.begin()}; it != graphs.end(); it++)
    {
        if(it.i->t()->isDrawn())
        {
            qDebug() << *it.i->t()->getExpression() << " has to be drawn";
            double currentMin{it.i->t()->getMin()};
            double currentMax{it.i->t()->getMax()};
            if(it == graphs.begin())
            {
                maxAbsoluteValue = (qAbs(currentMin) > qAbs(currentMax))?qAbs(currentMin):qAbs(currentMax);
            }


            if(maxAbsoluteValue < qAbs(currentMin))
            {
                maxAbsoluteValue = qAbs(currentMin);
            }
            if(maxAbsoluteValue < qAbs(currentMax))
            {
                maxAbsoluteValue = qAbs(currentMax);
            }
        }
    }

    qDebug() << "Max absolute value: " << maxAbsoluteValue;
    // Scaling
    //setUnitSegmentValue(areaWidth/(2*maxAbsoluteVal*gridCellWidth*cellQuantityInUnitSegment)); */

    // Draws the painting area
    drawGrid(painter);
    drawOriginPoint(painter);
    drawAxes(painter);
    drawCoordinates(painter);
    drawAxesNames(painter);




    //qDebug() << "new unit segment value: " << unitSegmentValue;


    for(Graph *item: graphs)
    {
        if(item->isDrawn() && !item->getExpression()->getInitialExpression().isEmpty())
        {
            double step{Graph::getSingleStep()};
            for(double x{item->getMin()+step}; x < item->getMax(); x+=step)
            {
                if(((*item)[x-step] != qInf()) &&
                   ((*item)[x-step] == (*item)[x-step])&&
                   ((*item)[x] != qInf()) &&
                   ((*item)[x] == (*item)[x]))
                {
                    //qDebug() << fromPaintingAreaToWidget(QPointF(x-step, (*item)[x-step])) <<
                    //            ": " << fromPaintingAreaToWidget(QPointF(x, (*item)[x]));
                    drawLineF(painter, QPointF(x-step, (*item)[x-step]), QPointF(x, (*item)[x]), item->getColor());
                }
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
    return QPointF(originPoint.x()+(x*gridCellWidth*cellQuantityInUnitSegment/unitSegmentValue),
                   originPoint.y()-(y*gridCellWidth*cellQuantityInUnitSegment/unitSegmentValue));
}

void PaintingArea::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << "Мышь движется по виджету!";
    //qDebug() << fromWidgetToPaintingArea(event->pos());
}

QSize PaintingArea::sizeHint() const
{
    return QSize(areaWidth+leftIndent, areaHeight+bottomIndent);
}

void PaintingArea::addFunction(MathExpression *function)
{
    //qDebug() << "Added new function: " << *function;
    Graph *newGraph = new Graph(function);
    graphs.append(newGraph);
}

void PaintingArea::changeGraphColor(int id, QColor color)
{
    //qDebug() << "Color of " << *function << " is changed!";
    for(Graph *item: graphs)
    {
        if(item->getExpression()->getId() == id)
        {
            item->setColor(color);
            if(item->isDrawn())
            {
                repaint();
            }
        }
    }
}

void PaintingArea::removeGraph(int id)
{
    //qDebug() << *function << " is deleted!";
    for(Graph *item: graphs)
    {
        if(item->getExpression()->getId() == id)
        {
            graphs.removeOne(item);
            delete item;
            break;
        }
    }
    repaint();
}

void PaintingArea::clearGraph(int id)
{
    //qDebug() << *function << " is cleared from plotter";
    for(Graph *item: graphs)
    {
        if(item->getExpression()->getId() == id)
        {
            item->setDrawn(false);
            repaint();
            break;
        }
    }
}

void PaintingArea::changeGraph(int id)
{
    //qDebug() << *function << " is changed! Recalculating of table of values";
    for(Graph *item: graphs)
    {
        if(item->getExpression()->getId() == id)
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

    int mathExpressionIdentificator;
    in >> mathExpressionIdentificator;
    qDebug() <<"Dropped expression's identificator: "<< mathExpressionIdentificator;

    for(Graph *item: graphs)
    {
        //qDebug() << "current expression: " << *item->getExpression();
        if(item->getExpression()->getId() == mathExpressionIdentificator)
        {
            item->setDrawn(true);
        }
    }
    repaint();
}
