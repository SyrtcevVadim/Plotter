#pragma once
#include"LibForPlotter/mathexpression.h"
#include"LibForPlotter/valuetable.h"
#include<QtWidgets>

class Plotter: public QWidget
{
    Q_OBJECT

private:
    /// Origin of coordinates
    QPointF origin;
    /// Width of grid cell
    int gridCellWidth;
    /// Cell quantity corresponding to unit segment
    int singleStep;
    /// Width of coordinate axeses
    int axesWidth;
    /// Width of origin point
    int originWidth;
    /// Width of the painting area
    int areaWidth;
    /// Height of the painting area
    int areaHeight;

    /// Stores tables of values of functions
    QList<ValueTable *> graphs;

protected:
    void paintEvent(QPaintEvent *event);
    // Methods for maintaining drag&drop mechanism
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    QSize sizeHint()const;

    /// Draws coordinate grid
    void drawGrid(QPainter *painter);
    /// Draws coordinate origin
    void drawOrigin(QPainter *painter);
    /// Draws coordinate axes
    void drawAxes(QPainter *painter);
    /// Draws rectangle border of painting area
    void drawAreaBorders(QPainter *painter);
    /// Draws coordinate numbers
    void drawCoordinates(QPainter *painter);

public:
    Plotter(QWidget *parentWidget = nullptr);
    Plotter(QSize *size, QWidget *parentWidget = nullptr);

    /// Sets grid cell width
    void setGridCellWidth(int width = 10);
    /// Sets coordinate origin width
    void setOriginWidth(double width = 5);
    /// Sets coordinate axeses width
    void setAxesWidth(double width = 0.5);
    /// Sets single step
    void setSingleStep(int cells = 1);



public slots:
    /// Draws axes names at painting area
    void drawAxesNames(QPainter *painter, QString hAxeName, QString vAxeName);
    /// Draws point with integral coordinates at painting area
    void drawPoint(QPainter *painter, QPoint point, QColor color = Qt::black);
    /// Draws poin with decimal coordinates at painting area
    void drawPointF(QPainter *painter, QPointF point, QColor color = Qt::black);
    /// Draws a line at painting area
    void drawLineF(QPainter *painter, QPointF startPoint, QPointF endPoint,QColor color = Qt::black);

    void addFunction(MathExpression *expression);
    void removeFunction(MathExpression *expression);
    void createTableValue(MathExpression *expression);
};

