#pragma once
#include<QtWidgets>

class Plotter: public QWidget
{
    Q_OBJECT

private:
    QPoint *origin;                       // Точка начала координат
    int gridCellWidth;                       // Длина стороны клетки
    int unitSegment;                        // Количество клеток под единичный отрезок
    int axesWidth;                          // Ширина координатных осей
    int originWidth;                        // Ширина точки начала координат

protected:
    void paintEvent(QPaintEvent *event);
    void drawGrid(QPainter *painter);       // Отрисовывает сетку
    void drawOrigin(QPainter *painter);     // Отрисовывает точку начала координат
    void drawAxes(QPainter *painter);       // Отрисовывает координатные оси


public:
    Plotter(QPoint *position, QSize *size, QWidget *parentWidget = 0);
    void setGridCellWidth(int width = 10);
    void setOriginWidth(int width = 3);
    void setAxesWidth(int width =1);
    void setUnitSegmentCells(int cells = 1);// Устанавливает длину единичного отрезка в клетках

public slots:
    void drawAxesNames(QPainter *painter, QString hAxeName, QString vAxeName);

};

