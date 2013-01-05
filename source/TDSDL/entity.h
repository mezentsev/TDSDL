#ifndef ENTITY_H
#define ENTITY_H

#include "sprite.h"

class Entity
{
private:
    Sprite* sprite;
    //Animation anim;
    int x,y;
    int state;
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
};

#endif // ENTITY_H
