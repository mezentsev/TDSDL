#ifndef MAP_H
#define MAP_H

#include <QList>
#include <QPoint>

class Map
{
private:
    int width,  height;
    int cell_w, cell_h;
    int *type;
    int *image;
    QList<QList<QPoint>*> routes;

public:
    Map (int width, int height, int cell_w, int cell_h);
    ~Map();

    void setCell (int x, int y, int type);
    void setMap  (int *type);
    int getWidth ();
    int getHeight();
    int getCell_w();
    int getCell_h();

    // Добавляет новый маршрут (пустой для заполнения)
    void addRoute();
    void addPoint(int num, int x, int y);
    QList<QPoint> * getRoute(int num);
    int getType(int x, int y);
};

#endif // MAP_H
