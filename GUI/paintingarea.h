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

    /// Width of cells in the coordinate grid
    double gridCellWidth;
    /// Thickness of coordinate grid's lines
    double gridLineThickness;
    /// Thickness of coordinate axes
    double axesThickness;
    /// Thickness of borders
    double borderThickness;
    /// Number of cells inside a unit segment
    int cellQuantityInUnitSegment;
    /// The value taken as a unit segment value
    double unitSegmentValue;
    /// Thickness of graphs on painting area
    double graphThickness;
    /// List of user-defined functions
    QList<Graph *> graphs;

    bool isDecimal(double value);


protected:
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    QSize sizeHint()const;

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
public:
    PaintingArea(const QSize &size, QWidget *parentWidget=nullptr);

    /// Sets width of origin point
    void setOriginPointThickness(double thickness);
    /// Sets the coordinate axes thickness
    void setAxesThickness(double thickness);
    /// Sets the grid's line thickness
    void setGridLineThickness(double thickness);
    /// Sets the width of grid's cells
    void setGridCellWidth(double width);
    void setGraphThickness(double value);
    /// Moves origin point to provided position
    void moveOriginPoint(const QPointF &pos);

public slots:
    void drawPointF(QPainter &painter, const QPointF &point, const QColor &color=Qt::black);
    void drawLineF(QPainter &painter, const QPointF &firstPoint, const QPointF &secondPoint, const QColor &color=Qt::black);
    void recalculateGraphs();
    void setUnitSegmentValue(double value);
    void setUnitSegmentCellQuantity(int cellQuantity);
    void setBorderThickness(double value);

    /// Adds new function to tracked functions
    void addFunction(MathExpression *function);
    /// Changes graph color of provided function
    void changeGraphColor(int id, QColor color);
    /// Removes graph from the painting area
    void removeGraph(int id);
    /// Clears graph from the painting area
    void clearGraph(int id);
    /// Changes graph of provided function
    void changeGraph(int id);
};

#endif // PAINTINGAREA_H
