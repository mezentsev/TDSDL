#ifndef PHYSICS_H
#define PHYSICS_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <QList>
#include <QPair>

class Physics : public QObject
{
    Q_OBJECT
private:
    float curSpeed;
    float maxSpeed;
    float x, y;
    float w, h;
    QList< QPair<float, float> > vertex; // Вершины против часовой

    b2BodyType type; //тип объекта (static/dynamic)
    QString data; // Инфа по объекту
    float density; // Плотность
    float friction; // Сопротивление

    b2World     * pHworld;
    b2Body      * pHbody;
    b2Fixture   * pHfixture;
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
        OIL,
        BUTTER
    };

    Physics();
    ~Physics();
    void setWorld(b2World *);
    void setShape(float x, float y, float w, float h);
    void createBody(void * data, float SCALE = 30.f);
    void setType(b2BodyType type);
    b2Body * getpHbody();
};

#endif // PHYSICS_H
