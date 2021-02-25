#pragma once
#include<QtWidgets>

class Plotter: public QWidget
{
    Q_OBJECT

private:
    /// Начало координат
    QPointF origin;
    /// Длина стороны клетки
    int gridCellWidth;
    /// Количество клеток, соответствующих единичному отрезку
    int singleTick;
    /// Толщина координатных осей
    int axesWidth;
    /// Ширина точки начала координат
    int originWidth;

protected:
    /// Вызывается для отрисовки всей графики
    void paintEvent(QPaintEvent *event);
    /// Отрисовывает координатную сетку
    void drawGrid(QPainter *painter);
    /// Отрисовывает точку начала координат
    void drawOrigin(QPainter *painter);
    /// Отрисовывает координатные оси
    void drawAxes(QPainter *painter);


public:
    Plotter(QPoint *position, QSize *size, QWidget *parentWidget = 0);
    /// Устанавливает длину стороны клетки
    void setGridCellWidth(int width = 10);
    /// Устанавливает ширину точки начала координат
    void setOriginWidth(int width = 3);
    /// Устанавливает толщину координатных осей
    void setAxesWidth(int width =1);
    /// Устанавливает длину единичного отрезка в клетках
    void setSingleTick(int cells = 1);



public slots:
    /// Отрисовывает названия координатных осей
    void drawAxesNames(QPainter *painter, QString hAxeName, QString vAxeName);
    /// Отрисовывает точку с целочисленными координатами на графике относительно начала координат
    void drawPoint(QPainter *painter,QPoint point, QColor color = Qt::black);

    void drawPointF(QPainter *painter, QPointF point, QColor color = Qt::black);

};

