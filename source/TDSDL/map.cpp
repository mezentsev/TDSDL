#include "map.h"

Map::Map(int width, int height)
{
    this->width  = width;
    this->height = height;
    this->type   = new int[width*height];
    this->image  = new int[width*height];
}

Map::~Map()
{
    qDeleteAll(this->routes.begin(), this->routes.end());
    this->routes.clear();
    delete [] this->type;
    delete [] this->image;
}

void Map::setCell(int x, int y, int type)
{
    this->type[y*this->width+x] = type;
}

void Map::setMap(int *type)
{
    this->type = type;
}

int Map::getWidth()
{
    return this->width;
}

int Map::getHeight()
{
    return this->height;
}

int Map::getCell_w()
{
    return this->cell_w;
}

int Map::getCell_h()
{
    return this->cell_h;
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

QList<QPoint> * Map::getRoute(int num)
{
    return this->routes[num];
}

int Map::getType(int x, int y)
{
    return this->type[y * this->width + x];
}
