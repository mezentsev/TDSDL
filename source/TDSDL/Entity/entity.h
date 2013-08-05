#ifndef ENTITY_H
#define ENTITY_H

#include "resources.h"
#include "Entity/animation.h"
#include "Entity/skeletal.h"
#include "Physics/physics.h"
#include <SFML/Graphics.hpp>
#include <QMap>
#include <typeinfo>
#include <QObject>

class Entity : public QObject
{
    Q_OBJECT
private:
    // Тип анимирования - спрайтовый/скелетный
    enum ANIM_TYPE{
        SPRITE, SKELETAL
    };

    ANIM_TYPE a_type;

    // Список анимаций
    QMap<QString, Animation*> anim;
    QMap<QString, Skeletal*> skeletal;

    // Координаты и угол поворота
    float x,y;
    float angle;

    // Полигон, который занимает Entity
    sf::ConvexShape polygon;

    // Название текущей анимации
    QString animName;

    float SCALE;

public:
    Physics phys;

    Entity(Animation * default_anim, int x, int y, sf::ConvexShape shape, QList<sf::ConvexShape> physShapes, b2World * world, Physics::B2_BODY_TYPE type, float SCALE);
    Entity(Animation *);
    Entity(Skeletal  *, b2World *, Physics::B2_BODY_TYPE);
    ~Entity();

    void setWorld(b2World *);
    void setType(Physics::B2_BODY_TYPE type);

    sf::IntRect rect; //спрайт

    Entity * setXY(float x, float y);
    Entity * setAngle(float angle);

    float getX();
    float getY();

    QList< sf::ConvexShape > getPhysShapeList();

    void move(float freq);

    bool addAnim(Animation * anim, QString name = "default"); //Привязывает анимацию с именем
    bool addAnim(Skeletal *, QString name = "default"); // Загружает скелет с именем
    bool setAnim(QString name); // Устанавливает анимацию с именем name
    void setDefault();
    sf::ConvexShape animate(sf::Time); //Проигрывает анимацию с именем this->animName и возвращает полигон

    // обновление физики
    virtual void doPhysics(float scale);
};

#endif // ENTITY_H
