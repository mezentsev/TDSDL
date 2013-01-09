#ifndef ENTITY_H
#define ENTITY_H

#include "resources.h"
#include <QMap>
#include "SDL/SDL_rotozoom.h"
#include <typeinfo>

class Entity
{
private:
    Sprite* sprite;
    QMap<QString, Animation*> anim;
    int x,y;
    int state; //Состояние объекта (возможно enum)
    int spriteX, spriteY; //смещение спрайта
    int w,h;
    QString animName;
    double _angle;
    double _scale;
public:
    Entity(Sprite* sprite, int x, int y, int w, int h, int state);
    Entity();
    ~Entity();

    Entity * setSprite(Sprite* sprite);
    Entity * setXY(int x, int y);
    Entity * setHW(int h, int w);
    int getX();
    int getY();
    int getW();
    int getH();
    void setState(int state);
    int getState();
    Entity * setAngle(double angle);
    Entity * setScale(double s);

    void refresh(SDL_Surface* dest);

    bool addAnim(Animation * anim, QString name); //Привязывает анимацию с именем
    Entity * setAnim(QString name); // Устанавливает анимацию с именем name
    Sprite * animate(); //Проигрывает анимацию с именем this->animName

    virtual const char* get_name(){return typeid(*this).name();}
};

#endif // ENTITY_H
