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
    /// Ширина области рисования графиков
    int areaWidth;
    /// Высота области рисования графиков
    int areaHeight;

protected:
    /// Вызывается для отрисовки всей графики
    void paintEvent(QPaintEvent *event);

    QSize sizeHint()const;

    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent *event);

    /// Отрисовывает координатную сетку
    void drawGrid(QPainter *painter);
    /// Отрисовывает точку начала координат
    void drawOrigin(QPainter *painter);
    /// Отрисовывает координатные оси
    void drawAxes(QPainter *painter);
    /// Отрисовываем прямоугольную границу плоскости
    void drawAreaBorders(QPainter *painter);
    /// Отрисовывает координаты системы
    void drawCoordinates(QPainter *painter);

public:
    Plotter(QWidget *parentWidget = nullptr);
    Plotter(QSize *size, QWidget *parentWidget = nullptr);
    /// Устанавливает длину стороны клетки
    void setGridCellWidth(int width = 10);
    /// Устанавливает ширину точки начала координат
    void setOriginWidth(double width = 5);
    /// Устанавливает толщину координатных осей
    void setAxesWidth(double width = 0.5);
    /// Устанавливает длину единичного отрезка в клетках
    void setSingleTick(int cells = 1);



public slots:
    /// Отрисовывает названия координатных осей
    void drawAxesNames(QPainter *painter, QString hAxeName, QString vAxeName);
    /// Отрисовывает точку с целочисленными координатами на графике относительно начала координат
    void drawPoint(QPainter *painter,QPoint point, QColor color = Qt::black);
    /// Отрисовывает точку с вещественными координатами на графике относительно начала координат
    void drawPointF(QPainter *painter, QPointF point, QColor color = Qt::black);
    /// Отрисовывает линию с вещественными координатами на графике относительно начала координат
    void drawLineF(QPainter *painter, QPointF startPoint, QPointF endPoint,QColor color = Qt::black);
};

