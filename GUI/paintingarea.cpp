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
    setGridCellWidth(15.0);
    setGraphThickness(1.5);
    setUnitSegmentValue(10.0);
    setUnitSegmentCellQuantity(2);

    // Adjusts the single step of a variable inside table of variables in dependence of the scale factor
    adjustSingleStep();
    qDebug() << "Single step for current scale: " << Graph::getSingleStep();

}

void PaintingArea::setUnitSegmentValue(double value)
{
    unitSegmentValue = value;
    adjustSingleStep();
    recalculateGraphs();
}

void PaintingArea::setUnitSegmentCellQuantity(int cellQuantity)
{
    cellQuantityInUnitSegment = cellQuantity;
    adjustSingleStep();
    recalculateGraphs();
    repaint();
}

void PaintingArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    adjustOXUnitSegmentValue();

    // Draws the painting area
    drawGrid(painter);
    drawOriginPoint(painter);
    drawAxes(painter);
    drawCoordinates(painter);
    drawAxesNames(painter);

    for(Graph *item: graphs)
    {
        if(item->isDrawn() && !item->getExpression()->getInitialExpression().isEmpty())
        {
            double step{Graph::getSingleStep()};
            for(double x{item->getMin()+step}; x < item->getMax(); x+=step)
            {
                if(isDecimal((*item)[x-step])&&isDecimal((*item)[x]))
                {
                    drawLineF(painter, QPointF(x-step, (*item)[x-step]), QPointF(x, (*item)[x]), item->getColor());
                }
            }
        }
    }
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
    adjustSingleStep();
    recalculateGraphs();
    repaint();
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
    int precision = (QString().setNum(unitSegmentValue).contains("."))?(1):(0);
    // Draws serifs after every unit segment on vertical axe
    // From origin point in positive direction
    for(double y{originPoint.y()}; y >= gridCellWidth; y-=gridCellWidth*cellQuantityInUnitSegment)
    {
        painter.drawLine(QPoint(originPoint.x()-3, y), QPoint(originPoint.x()+3, y));
        painter.drawText(0, y+4, QString().setNum(currentValue, 'f', precision));
        currentValue+= unitSegmentValue;
    }
    currentValue = -unitSegmentValue;
    // From origin point in negative direction
    for(double y{originPoint.y()+gridCellWidth*cellQuantityInUnitSegment}; y <= areaHeight; y+= gridCellWidth*cellQuantityInUnitSegment)
    {
        painter.drawLine(QPoint(originPoint.x()-3, y), QPoint(originPoint.x()+3, y));
        painter.drawText(0, y+4, QString().setNum(currentValue, 'f', precision));
        currentValue -= unitSegmentValue;
    }

    currentValue = 0.0;
    // Draws serifs after every unit segment on horizontal axe
    // From origin point in positive direction
    int i{0};
    for(double x{originPoint.x()}; x < areaWidth+leftIndent-gridCellWidth; x+=gridCellWidth*cellQuantityInUnitSegment, i++)
    {
        painter.drawLine(QPoint(x, originPoint.y()+3), QPoint(x, originPoint.y()-3));
        if(i %2 == 0)
        {
            painter.drawText(x-3, areaHeight+12,QString().setNum(currentValue, 'f', precision));
        }
        else
        {
            painter.drawText(x-3, areaHeight+18,QString().setNum(currentValue, 'f', precision));
        }
        currentValue += unitSegmentValue;
    }
    currentValue = -unitSegmentValue;
    // From origin point in negative direction
    i = 0;
    for(double x{originPoint.x()-gridCellWidth*cellQuantityInUnitSegment}; x >= leftIndent; x-= gridCellWidth*cellQuantityInUnitSegment,i++)
    {
        painter.drawLine(QPoint(x, originPoint.y()+3), QPoint(x, originPoint.y()-3));
        if(i % 2 ==1)
        {
            painter.drawText(x-7, areaHeight+12,QString().setNum(currentValue, 'f', precision));
        }
        else
        {
            painter.drawText(x-7, areaHeight+18,QString().setNum(currentValue, 'f', precision));
        }
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
    Graph *newGraph = new Graph(function);
    graphs.append(newGraph);
}

void PaintingArea::changeGraphColor(int id, QColor color)
{
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
    if(event->mimeData()->hasFormat("MathExpression"))
    {
        event->acceptProposedAction();
    }
}

void PaintingArea::dropEvent(QDropEvent *event)
{
    QByteArray byteArray(event->mimeData()->data("MathExpression"));
    QDataStream in(&byteArray, QIODevice::ReadOnly);

    int mathExpressionIdentificator;
    in >> mathExpressionIdentificator;

    for(Graph *item: graphs)
    {
        if(item->getExpression()->getId() == mathExpressionIdentificator)
        {
            item->setDrawn(true);
        }
    }
    repaint();
}

bool PaintingArea::isDecimal(double value)
{
    if((value == value)&&(value != qInf()))
    {
        return true;
    }
    return false;
}

void PaintingArea::recalculateGraphs()
{
    for(Graph *graph: graphs)
    {
        graph->recalculate();
    }
}

bool PaintingArea::isInsidePaintingArea(const QPointF &point)
{
    if(leftIndent <= fromPaintingAreaToWidget(point).x() && fromPaintingAreaToWidget(point).y() <= areaHeight)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PaintingArea::adjustSingleStep()
{
    Graph::setSingleStep((unitSegmentValue*graphThickness)/(gridCellWidth*cellQuantityInUnitSegment));
}

void PaintingArea::adjustOXUnitSegmentValue()
{
    // Adjusting scale for OX axe
    double maxAbsoluteValue{0.0};
    for(auto it{graphs.begin()}; it != graphs.end(); it++)
    {
        if(it.i->t()->isDrawn())
        {
            double currentMin{qAbs(it.i->t()->getMin())};
            double currentMax{qAbs(it.i->t()->getMax())};
            if(it == graphs.begin())
            {
                maxAbsoluteValue = max(currentMin, currentMax);
            }


            maxAbsoluteValue = max(currentMin, maxAbsoluteValue);
            maxAbsoluteValue = max(currentMax ,maxAbsoluteValue);
        }
    }


    // Scaling on OX axis
    if(maxAbsoluteValue == 0)
    {
        setUnitSegmentValue((2*20.0*gridCellWidth*cellQuantityInUnitSegment)/(areaWidth-4*gridCellWidth));
        qDebug() << "Single step corresponding to the max abs val " << (2*20.0*gridCellWidth*cellQuantityInUnitSegment)/(areaWidth-4*gridCellWidth);
    }
    else
    {
        setUnitSegmentValue((2*maxAbsoluteValue*gridCellWidth*cellQuantityInUnitSegment)/(areaWidth-4*gridCellWidth));
        qDebug() << "Single step corresponding to the max abs val " << (2*maxAbsoluteValue*gridCellWidth*cellQuantityInUnitSegment)/(areaWidth-4*gridCellWidth);
    }



}

void PaintingArea::adjustOYUnitSegmentValue()
{

}

double PaintingArea::max(double first, double second)
{
    if(first > second)
    {
        return first;
    }
    return second;
}
