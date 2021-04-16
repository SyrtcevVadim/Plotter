#include"GUI/plotter.h"
#include"LibForPlotter/mathexpression.h"
#include"LibForPlotter/valuetable.h"
#include<QtWidgets>

Plotter::Plotter(QSize *size, QWidget *parent): QWidget(parent)
{
    setAcceptDrops(true);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setCursor(Qt::CrossCursor);

    setGridCellWidth(10);
    setOriginWidth(6);
    setAxesWidth(0.5);
    setSingleStep(4);

    resize(size->width(),size->height());

    areaWidth = size->width() - 2*gridCellWidth;
    areaHeight = size->height() - 2*gridCellWidth;

    origin.setX(areaWidth / 2);
    origin.setY(areaHeight / 2);
}


void Plotter::paintEvent(QPaintEvent *event)
{
    // Не используем параметр event
    Q_UNUSED(event);

    // Данный объект занимается отрисовкой всей графики
    QPainter painter(this);

    drawAreaBorders(&painter);
    drawGrid(&painter);
    drawOrigin(&painter);
    drawAxes(&painter);
    drawAxesNames(&painter, QString("X"), QString("Y"));
    drawCoordinates(&painter);

    // Отрисовываем графики функций
    for(ValueTable *table: graphs)
    {
        if(table->isDrawn())
        {
            for(double var{table->getMin()}; var <= table->getMax(); var+=table->getSingleStep())
            {
                drawLineF(&painter, QPointF(var-table->getSingleStep(), table->get(var-table->getSingleStep())), QPointF(var, table->get(var)));
            }
        }
    }

    //drawLineF(&painter, QPointF(-3.0, 3.0), QPointF(3.0, 3.0), Qt::darkRed);
    //drawLineF(&painter, QPointF(-5.0, -5.0), QPointF(1.0, 1.0), Qt::darkYellow);

}

void Plotter::setGridCellWidth(int width)
{
    gridCellWidth = width;
}

void Plotter::setOriginWidth(double width)
{
    originWidth = width;
}

void Plotter:: setSingleStep(int cells)
{
    singleStep = cells;
}

void Plotter::setAxesWidth(double width)
{
    axesWidth = width;
}

void Plotter::drawGrid(QPainter *painter)
{
    QPen pen(Qt::gray, .3);
    painter ->setPen(pen);

    // Сетка привязана к началу координат

    // Отрисовываем вертикальные линии
    // От точки отсчёта налево
    for(int x = origin.x(); x >=0; x-=gridCellWidth)
    {
        QPoint topPoint(x, 0);
        QPoint bottomPoint(x, areaHeight);
        painter->drawLine(topPoint, bottomPoint);
    }
    // От точки отсчёта направо
    for(int x = origin.x()+gridCellWidth; x <= areaWidth; x+=gridCellWidth)
    {
        QPoint topPoint(x, 0);
        QPoint bottomPoint(x, areaHeight);
        painter->drawLine(topPoint, bottomPoint);
    }

    // Отрисовываем горизонтальные линии
    // От точки отсчёта вверх
    for(int y = origin.y(); y >= 0; y-= gridCellWidth)
    {
        QPoint leftPoint(0, y);
        QPoint rightPoint(areaWidth, y);
        painter ->drawLine(leftPoint, rightPoint);
    }
    // От точки отсчёта вниз
    for(int y = origin.y(); y <= areaHeight; y += gridCellWidth)
    {
        QPoint leftPoint(0, y);
        QPoint rightPoint(areaWidth, y);
        painter ->drawLine(leftPoint, rightPoint);
    }
}

void Plotter::drawAreaBorders(QPainter *painter)
{
    QPen pen(Qt::darkGray, 3);
    painter ->setPen(pen);
    // Отрисовывает прямоугольную границу
    painter ->drawRect(0, 0, width(), height());
}

void Plotter::drawCoordinates(QPainter *painter)
{
    QPen pen(Qt::black, 5);
    painter ->setPen(pen);

    // Отрисовываем координаты по горизонтальной оси
    // От начала координат налево
    int coordinateCounter{0};
    for(int x = origin.x(); x >= gridCellWidth*singleStep; x -= gridCellWidth*singleStep)
    {
        if(coordinateCounter == 0)
        {
            painter -> drawText(x, areaHeight+gridCellWidth, QString().setNum(coordinateCounter--));
        }
        else
        {
            painter -> drawText(x - gridCellWidth/2, areaHeight+gridCellWidth, QString().setNum(coordinateCounter--));
        }
    }
    coordinateCounter = 1;
    // От начала координат направо
    for(int x = origin.x() + gridCellWidth*singleStep; x <= areaWidth-gridCellWidth*singleStep; x += gridCellWidth*singleStep)
    {
        painter ->drawText(x, areaHeight + gridCellWidth, QString().setNum(coordinateCounter++));
    }

    coordinateCounter  = 0;
    // Отрисовываем координаты по вертикальной оси
    // От начала координат наверх
    for(int y = origin.y(); y >= gridCellWidth*singleStep; y -= gridCellWidth*singleStep)
    {
        if(coordinateCounter == 0)
        {
            painter -> drawText(areaWidth+gridCellWidth/2, y + gridCellWidth/2  ,QString().setNum(coordinateCounter++));
        }
        else
        {
            painter -> drawText(areaWidth + gridCellWidth/2, y + gridCellWidth/3, QString().setNum(coordinateCounter++));
        }
    }
    coordinateCounter = -1;
    // От начала координат вниз
    for(int y = origin.y() + gridCellWidth*singleStep; y <= areaHeight -gridCellWidth*singleStep; y += gridCellWidth*singleStep)
    {
        painter -> drawText(areaWidth + gridCellWidth/2, y , QString().setNum(coordinateCounter--));
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
    QPoint topPoint(origin.x(), 0);
    QPoint bottomPoint(origin.x(), areaWidth);
    painter ->drawLine(topPoint, bottomPoint);

    // Отрисовываем горизонтальную ось
    QPoint leftPoint(0, origin.y());
    QPoint rightPoint(areaWidth, origin.y());

    painter ->drawLine(leftPoint, rightPoint);

    // Изображаем единичные засечки
    // Засечки на горизонтальной оси
    // В направлении положительных координат
    for(int xcoord = origin.x()+gridCellWidth*singleStep; xcoord <= areaWidth; xcoord += gridCellWidth*singleStep)
    {
        QPoint bottomPoint(xcoord, origin.y() + gridCellWidth / 3);
        QPoint topPoint(xcoord, origin.y() - gridCellWidth / 3);
        painter -> drawLine(bottomPoint, topPoint);
    }
    // В направлении отрицательных координат
    for(int xcoord = origin.x()-gridCellWidth*singleStep; xcoord > 0; xcoord -= gridCellWidth*singleStep)
    {
        QPoint bottomPoint(xcoord, origin.y() + gridCellWidth / 3);
        QPoint topPoint(xcoord, origin.y() - gridCellWidth / 3);
        painter -> drawLine(bottomPoint, topPoint);
    }


    // Засечки на вертикальной оси
    //  В направлении положительных координат
    for(int ycoord = origin.y() - gridCellWidth*singleStep; ycoord >0; ycoord -= gridCellWidth*singleStep)
    {
        QPoint leftPoint(origin.x() - gridCellWidth/3, ycoord);
        QPoint rightPoint(origin.x() + gridCellWidth/3, ycoord);
        painter -> drawLine(leftPoint, rightPoint);
    }

    // В направлении отрицательных координат
    for(int ycoord = origin.y() + gridCellWidth*singleStep; ycoord <= areaHeight; ycoord += gridCellWidth*singleStep)
    {
        QPoint leftPoint(origin.x() - gridCellWidth/3, ycoord);
        QPoint rightPoint(origin.x() + gridCellWidth/3, ycoord);
        painter -> drawLine(leftPoint, rightPoint);
    }

    // Отрисовываем стрелки, показывающие положительное направление на осях координат
    // На горизонтальных осях
    painter ->drawLine(areaWidth, origin.y(), areaWidth-gridCellWidth, origin.y()+gridCellWidth/2);
    painter ->drawLine(areaWidth, origin.y(), areaWidth-gridCellWidth, origin.y()-gridCellWidth/2);

    // На вертикальных осях
    painter ->drawLine(origin.x(), 0, origin.x()+gridCellWidth/2, gridCellWidth);
    painter ->drawLine(origin.x(), 0, origin.x()-gridCellWidth/2, gridCellWidth);
}

void Plotter::drawAxesNames(QPainter *painter, QString horizontalAxeName, QString verticalAxeName)
{
    QPen pen(Qt::black, 3);
    painter ->setPen(pen);

    // Название горизонтальной оси
    painter->drawText(areaWidth-gridCellWidth+2, origin.y()+gridCellWidth*2, horizontalAxeName);

    // Название вертикальной оси
    painter ->drawText(origin.x() + gridCellWidth+2, 0 + gridCellWidth+2, verticalAxeName);
}

void Plotter::drawPoint(QPainter *painter, QPoint point, QColor color)
{
    QPen pen{color, 3};
    painter->setPen(pen);

    painter->drawPoint(origin.x()+(point.x()*gridCellWidth*singleStep), origin.y()-(point.y()*gridCellWidth*singleStep));
}

void Plotter::drawPointF(QPainter *painter, QPointF point, QColor color)
{
    QPen pen{color, 1.0};
    painter->setPen(pen);

    painter->drawPoint(origin.x()+(point.x()*gridCellWidth*singleStep), origin.y()-(point.y()*gridCellWidth*singleStep));

}

void Plotter::drawLineF(QPainter *painter, QPointF startPoint, QPointF endPoint, QColor color)
{
    QPen pen{color, 1};
    painter ->setPen(pen);

    painter->drawLine(origin.x() +(startPoint.x()*gridCellWidth*singleStep),
                      origin.y() - (startPoint.y()*gridCellWidth*singleStep),
                      origin.x() +(endPoint.x()*gridCellWidth*singleStep),
                      origin.y() - (endPoint.y()*gridCellWidth*singleStep));
}

QSize Plotter::sizeHint() const
{
    return QSize(width(), height());
}

void Plotter::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "DragEnterEvent!";
    if(event->mimeData()->hasFormat("MathExpression"))
    {
        event->acceptProposedAction();
    }
}

void Plotter::dropEvent(QDropEvent *event)
{
    qDebug() << "DropEvent!";
    QByteArray byteArray(event->mimeData()->data("MathExpression"));
    QDataStream in(&byteArray, QIODevice::ReadOnly);

    MathExpression expression;
    in >> expression;
    qDebug() <<"Dropped expression: "<< expression;

    for(ValueTable *item: graphs)
    {
        qDebug() << "current expression: " << item->getExpression();
        if(item->getExpression()->GetInfixExpression() == expression.GetInfixExpression())
        {
            qDebug() << expression << " is found inside plotter!";
            item->setDrawn();
        }
    }
    repaint();

}

void Plotter::addFunction(MathExpression *expression)
{
    qDebug() << "Added new expression:\n"<<*expression;
    ValueTable *newGraph = new ValueTable(expression);
    graphs.append(newGraph);
}

void Plotter::removeFunction(MathExpression *expression)
{
    for(ValueTable *item: graphs)
    {
        if(item->getExpression() == expression)
        {
            graphs.removeOne(item);
            delete item;
            break;
        }
    }
    repaint();
}

void Plotter::createTableValue(MathExpression *expression)
{
    qDebug() << "Expression is changed: " << *expression;
    for(ValueTable *item: graphs)
    {
        if(item->getExpression() == expression)
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
