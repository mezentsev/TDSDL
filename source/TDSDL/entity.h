#ifndef ENTITY_H
#define ENTITY_H

#include "resources.h"
#include "animation.h"
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

    int w,h;
    QString animName;

public:

    Entity(Animation * default_anim, int x, int y, int w, int h);
    Entity();
    ~Entity();

    sf::IntRect rect; //спрайт

    Entity * setXY(float x, float y);
    Entity * setHW(int h, int w);
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

    virtual const char* get_name(){return typeid(*this).name();}
};

#endif // ENTITY_H
