#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H
#include"LibForPlotter/graph.h"
#include<QtWidgets>

class PaintingArea: public QWidget
{
    Q_OBJECT

private:
    /// Origin point of the coordinate system
    QPointF originPoint;
    /// Thickness of the origin point
    double originPointThickness;
    /// Width of painting area
    double areaWidth;
    /// Height of painting area
    double areaHeight;
    /// Offset from the left coordinate side
    double leftIndent;
    /// Offset from the bottom coordinte side
    double bottomIndent;

    /// The x coordinate of origin point
    double originPointXValue;
    /// The y coordinate of origin point
    double originPointYValue;

    /// The minimum value of x coordinate on OX axis
    double lowestXValue;
    /// The maximum value of x coordinate on OX axis
    double highestXValue;

    /// The minimum value of y coordinate on OY axis
    double lowestYValue;
    /// The maximum value of y coordinate on OY axis
    double highestYValue;

    /// Width of cells in the coordinate grid
    double gridCellWidth;
    /// Thickness of coordinate grid's lines
    double gridLineThickness;
    /// Thickness of coordinate axes
    double axisThickness;
    /// Number of cells inside a unit segment for both OX and OY axis
    int cellQuantityInUnitSegment;

    /// The value taken as a unit segment value of OX axis
    double unitSegmentOXValue;
    /// The value taken as a unit segment value of OY axis
    double unitSegmentOYValue;
    /// Thickness of graphs' lines on painting area
    double graphThickness;
    /// List of user-defined functions
    QList<Graph *> graphs;

    /// Checks whether number is deimal or not
    bool isDecimal(double value);

    /// Supports the correctness of asymptotes
    bool isCorrect(double y1, double y2);


protected:
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    QSize sizeHint()const;

    /// Draws origin point
    void drawOriginPoint(QPainter &painter);
    /// Draws coordinate grid
    void drawGrid(QPainter &painter);
    /// Draws coordinate axes
    void drawAxes(QPainter &painter);
    /// Draws coordinate labels on the left and bottom side of the painting area
    void drawCoordinates(QPainter &painter);
    /// Draws the coordinate axes names on painting area
    void drawAxesNames(QPainter &painter);

    /// Convert widget coordinates to painting area coordinates
    QPointF fromWidgetToPaintingArea(const QPointF &coord);
    /// Convert painting area coordinates to widget coordinates
    QPointF fromPaintingAreaToWidget(const QPointF &coord);

    /// Checks whether point is inside painting area
    bool isInsidePaintingArea(const QPointF &point);
    void adjustSingleStep();
    /// Adjusts the unit segment value of OX axis
    void adjustOXUnitSegmentValue();
    /// Adjusts the unit segment value of OY axis
    void adjustOYUnitSegmentValue();
public:
    PaintingArea(const QSize &size, QWidget *parentWidget=nullptr);

    /// Sets width of origin point
    void setOriginPointThickness(double thickness);
    /// Sets the coordinate axes thickness
    void setAxisThickness(double thickness);
    /// Sets the grid's line thickness
    void setGridLineThickness(double thickness);
    /// Sets the width of grid's cells
    void setGridCellWidth(double width);
    void setGraphThickness(double value);
    /// Moves origin point to provided position
    void moveOriginPoint(const QPointF &pos);

public slots:
    ///
    void drawPointF(QPainter &painter, const QPointF &point, const QColor &color=Qt::black);
    ///
    void drawLineF(QPainter &painter, const QPointF &firstPoint, const QPointF &secondPoint, const QColor &color=Qt::black);
    ///
    void recalculateGraphs();
    ///
    void setUnitSegmentCellQuantity(int cellQuantity);

    /// Adds new function to tracked functions
    void addFunction(MathExpression *function);
    /// Changes graph color of provided function
    void changeGraphColor(int id, QColor color);
    /// Removes graph from the painting area
    void removeGraph(int id);
    /// Clears graph from the painting area
    void clearGraph(int id);
    /// Changes graph of provided function
    void recalculateGraph(int id);

    /// Sets the range of x coordinates
    void setOXRestriction(double min, double max);
    /// Sets the range of y coordinates
    void setOYRestriction(double min, double max);
};

#endif // PAINTINGAREA_H
