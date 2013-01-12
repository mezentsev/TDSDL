#ifndef ENTITY_H
#define ENTITY_H

#include "resources.h"
#include "animation.h"
#include <SFML/Graphics.hpp>
#include <QMap>
#include <typeinfo>

class Entity
{
private:
    sf::Sprite *sprite;
    QMap<QString, Animation*> anim;
    float x,y;
    int state; //Состояние объекта (возможно enum)
    sf::IntRect rect; //спрайт
    int w,h;
    QString animName;
    double _angle;
    double _scale;
public:
    Entity(sf::Sprite* sprite, int x, int y, int w, int h, int state);
    Entity();
    ~Entity();

    //Entity * setSprite(sf::Sprite* sprite);
    Entity * setXY(float x, float y);
    Entity * setHW(int h, int w);
    float getX();
    float getY();
    int getW();
    int getH();
    void setState(int state);
    int getState();
    Entity * setAngle(double angle);
    Entity * setScale(double s);

    void refresh(sf::RenderWindow *screen);

    bool addAnim(Animation * anim, QString name); //Привязывает анимацию с именем
    Entity * setAnim(QString name); // Устанавливает анимацию с именем name
    sf::Sprite * animate(sf::RenderWindow *screen); //Проигрывает анимацию с именем this->animName

    virtual const char* get_name(){return typeid(*this).name();}
};

#endif // ENTITY_H
