#ifndef PHYSICS_H
#define PHYSICS_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <SFML/Graphics/ConvexShape.hpp>
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

    QList< b2PolygonShape >     shape;
    b2BodyType type; //тип объекта (static/dynamic)
    void * data; // Инфа по объекту
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

    enum B2_BODY_TYPE{
        DYNAMIC = b2_dynamicBody,
        STATIC  = b2_staticBody
    };

    Physics();
    ~Physics();
    void setWorld(b2World *);
    void setShape(float x, float y, b2PolygonShape);
    void setShape(float x, float y, sf::ConvexShape);
    QList< b2PolygonShape > &getShapeList();
    void createBody(void * data, float SCALE = 30.f);
    void setType(B2_BODY_TYPE type);
    b2Body * getpHbody();
    float getGravity();
    bool isContactDown();
    bool isContactRight();
    bool isContactLeft();
};

#endif // PHYSICS_H
