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
    setAxisThickness(0.5);
    setGridLineThickness(0.5);
    setBorderThickness(2.5);
    setGridCellWidth(15.0);
    setGraphThickness(1.5);
    setUnitSegmentCellQuantity(2);
    cellQuantityInUnitSegmentOY = 2;

    unitSegmentOXValue = 10.0;
    unitSegmentOYValue = 10.0;
    unitSegmentOXValue = (2*10.0*gridCellWidth*cellQuantityInUnitSegmentOX)/(areaWidth-4*gridCellWidth);
    unitSegmentOYValue = (2*10.0*gridCellWidth*cellQuantityInUnitSegmentOY)/(areaWidth);


    // Adjusts the single step of a variable inside table of variables in dependence of the scale factor
    adjustSingleStep();
}


void PaintingArea::setUnitSegmentCellQuantity(int cellQuantity)
{
    cellQuantityInUnitSegmentOX = cellQuantity;
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
            for(double x{item->getLeftBorder()+step}; x < item->getRightBorder()-2*step; x+=step)
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

void PaintingArea::setAxisThickness(double value)
{
    axisThickness = value;
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
    QPen pen(Qt::black, axisThickness);
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
    int precision = (QString().setNum(unitSegmentOXValue).contains("."))?(1):(0);
    // Draws serifs after every unit segment on vertical axe
    // From origin point in positive direction
    for(double y{originPoint.y()}; y >= gridCellWidth; y-=gridCellWidth*cellQuantityInUnitSegmentOY)
    {
        painter.drawLine(QPoint(originPoint.x()-3, y), QPoint(originPoint.x()+3, y));
        painter.drawText(0, y+4, QString().setNum(currentValue, 'f', precision));
        currentValue+= unitSegmentOYValue;
    }
    currentValue = -unitSegmentOYValue;
    // From origin point in negative direction
    for(double y{originPoint.y()+gridCellWidth*cellQuantityInUnitSegmentOY}; y <= areaHeight; y+= gridCellWidth*cellQuantityInUnitSegmentOY)
    {
        painter.drawLine(QPoint(originPoint.x()-3, y), QPoint(originPoint.x()+3, y));
        painter.drawText(0, y+4, QString().setNum(currentValue, 'f', precision));
        currentValue -= unitSegmentOYValue;
    }

    currentValue = 0.0;
    // Draws serifs after every unit segment on horizontal axe
    // From origin point in positive direction
    int i{0};
    for(double x{originPoint.x()}; x < areaWidth+leftIndent-gridCellWidth; x+=gridCellWidth*cellQuantityInUnitSegmentOX, i++)
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
        currentValue += unitSegmentOXValue;
    }
    currentValue = -unitSegmentOXValue;
    // From origin point in negative direction
    i = 0;
    for(double x{originPoint.x()-gridCellWidth*cellQuantityInUnitSegmentOX}; x >= leftIndent; x-= gridCellWidth*cellQuantityInUnitSegmentOX,i++)
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
        currentValue -= unitSegmentOXValue;
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
    return QPointF(((x-originPoint.x())*unitSegmentOXValue)/(gridCellWidth*cellQuantityInUnitSegmentOX),
                   ((originPoint.y()-y)*unitSegmentOYValue)/(gridCellWidth*cellQuantityInUnitSegmentOY));
}

QPointF PaintingArea::fromPaintingAreaToWidget(const QPointF &coord)
{
    double x = coord.x();
    double y = coord.y();
    return QPointF(originPoint.x()+(x*gridCellWidth*cellQuantityInUnitSegmentOX/unitSegmentOXValue),
                   originPoint.y()-(y*gridCellWidth*cellQuantityInUnitSegmentOY/unitSegmentOYValue));
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
            repaint();
            break;
        }
    }
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

void PaintingArea::recalculateGraph(int id)
{
    for(Graph *item: graphs)
    {
        if(item->getExpression()->getId() == id)
        {
            item->recalculate();
            if(item->isDrawn())
            {
                adjustOYUnitSegmentValue();
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
            adjustOYUnitSegmentValue();
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
    Graph::setSingleStep((5*unitSegmentOXValue*graphThickness)/(gridCellWidth*cellQuantityInUnitSegmentOX));
    qDebug() << "single step: "<< Graph::getSingleStep();
}

void PaintingArea::adjustOXUnitSegmentValue()
{
    // Adjusting scale for OX axe
    double maxAbsoluteValue{0.0};
    for(auto it{graphs.begin()}; it != graphs.end(); it++)
    {
        if(it.i->t()->isDrawn())
        {
            double currentMin{qAbs(it.i->t()->getLeftBorder())};
            double currentMax{qAbs(it.i->t()->getRightBorder())};
            if(it == graphs.begin())
            {
                maxAbsoluteValue = qMax(currentMin, currentMax);
            }


            maxAbsoluteValue = qMax(currentMin, maxAbsoluteValue);
            maxAbsoluteValue = qMax(currentMax ,maxAbsoluteValue);
        }
    }
    qDebug() << "Max x value: " << maxAbsoluteValue;
    // Scaling on OX axis
    if(maxAbsoluteValue == 0.0)
    {
        unitSegmentOXValue = (2*10.0*gridCellWidth*cellQuantityInUnitSegmentOX)/(areaWidth-4*gridCellWidth);
    }
    else
    {
        unitSegmentOXValue = (2*maxAbsoluteValue*gridCellWidth*cellQuantityInUnitSegmentOX)/(areaWidth-4*gridCellWidth);
    }
    adjustSingleStep();
}


void PaintingArea::adjustOYUnitSegmentValue()
{
    double maxAbsoluteValue{0.0};
    for(auto it{graphs.begin()}; it != graphs.end(); it++)
    {
        if(it.i->t()->isDrawn())
        {
            double currMaxValue{it.i->t()->getMaxAbsoluteValue()};
            if(it == graphs.begin())
            {
                maxAbsoluteValue = currMaxValue;
            }
            maxAbsoluteValue = qMax(currMaxValue, maxAbsoluteValue);
        }
    }
    qDebug() << "Max OY: " << maxAbsoluteValue;
    if(maxAbsoluteValue == 0)
    {
        unitSegmentOYValue = (2*10.0*gridCellWidth*cellQuantityInUnitSegmentOY)/(areaWidth);
    }
    else
    {
        unitSegmentOYValue = (2*maxAbsoluteValue*gridCellWidth*cellQuantityInUnitSegmentOY)/(areaWidth);
    }
    adjustSingleStep();
}


