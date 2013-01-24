#ifndef ENTITY_H
#define ENTITY_H

#include "resources.h"
#include "animation.h"
#include "physics.h"
#include <SFML/Graphics.hpp>
#include <QMap>
#include <typeinfo>
#include <QObject>

class Entity : public QObject
{
    Q_OBJECT
private:
    QMap<QString, Animation*> anim;
    float x,y;
    float angle;

    int w,h;
    QString animName;

    float SCALE;

public:
    Physics phys;

    Entity(Animation * default_anim, int x, int y, int w, int h, b2World * world, Physics::B2_BODY_TYPE type, float SCALE);
    ~Entity();

    sf::IntRect rect; //спрайт

    Entity * setXY(float x, float y);
    Entity * setHW(int h, int w);
    Entity * setAngle(float angle);

    float getX();
    float getY();
    int getW();
    int getH();

    sf::Sprite * refresh(sf::Time);
    void move(float freq);

    bool addAnim(Animation * anim, QString name); //Привязывает анимацию с именем
    bool setAnim(QString name); // Устанавливает анимацию с именем name
    void setDefault();
    sf::Sprite * animate(sf::Time); //Проигрывает анимацию с именем this->animName

    virtual void doPhysics(float scale);
};

#endif // ENTITY_H
