#ifndef PHYSICS_H
#define PHYSICS_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <QList>
#include <QPair>

class physics : public QObject
{
    Q_OBJECT
private:
    float curSpeed;
    float maxSpeed;
    float mas;
    float x, y;
    QList<QPair(float x, float y)> vertex; // Вершины против часовой

    b2BodyType type; //тип объекта (static/dynamic)
    QString data; // Инфа по объекту
    float density; // Плотность
    float friction; // Сопротивление

    b2Body* Body;

public:
    enum BODY_TYPE{
        GROUND,
        WALL,
        UNIT,
        BULLET
    };
    enum MATERIAL_TYPE{
        WATER,
        AIR,
        SAND,
        WOOD,
        STONE,
        INK,
        OIL
    };

    physics();
    ~physics();
};

#endif // PHYSICS_H
