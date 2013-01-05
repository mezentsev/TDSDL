#include "map.h"

Map::Map(int width, int height, int cell_w, int cell_h)
{
    this->width  = width;
    this->height = height;
    this->cell_w = cell_w;
    this->cell_h = cell_h;
    this->type  = new int[width*height];
}

Map::~Map()
{
    this->routes.clear();
    delete [] this->type;
}



void Map::setCell(int x, int y, int type)
{
    this->type[y*this->width+x] = type;
}

void Map::setMap(int *type)
{
    this->type = type;
}

void Map::addRoute()
{
    QList<QPoint> *list = new QList<QPoint>;
    this->routes.append(list);
}

void Map::addPoint(int num, int x, int y)
{
    if (num < this->routes.count())
    {
        QList<QPoint> *list = this->routes.value(num);
        QPoint point;
        point.setX(x);
        point.setY(y);
        list->append(point);
        this->routes[num] = list;
    }
}

QList<QPoint> Map::getRoute(int num)
{
    return *this->routes[num];
}

int Map::getType(int x, int y)
{
    return this->type[y*this->width+x];
}

