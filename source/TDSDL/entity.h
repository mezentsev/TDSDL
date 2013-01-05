#ifndef ENTITY_H
#define ENTITY_H

#include "resources.h"
#include <QMap>

class Entity
{
private:
    Sprite* sprite;
    QMap<QString, Animation*> anim;
    int x,y;
    int state; //Состояние объекта (возможно enum)
    QString animName;
public:
    Entity(Sprite* sprite, int x, int y, int state);
    Entity();
    ~Entity();

    void setSprite(Sprite* sprite);
    void setXY(int x, int y);
    int getX();
    int getY();
    void setState(int state);
    int getState();

    void refresh(SDL_Surface* dest);

    bool addAnim(Animation * anim, QString name); //Привязывает анимацию с именем
    Entity * setAnim(QString name); // Устанавливает анимацию с именем name
    bool animate(); //Проигрывает анимацию с именем this->animName
};

#endif // ENTITY_H
