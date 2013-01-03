#ifndef ENTITY_H
#define ENTITY_H

#include "sprite.h"

class Entity
{
private:
    Sprite sprite;
    //Animation anim;
    int x,y;
    int state;
    int type;
public:
    Entity(Sprite sprite, int x, int y, int state, int type );
    ~Entity();
};

#endif // ENTITY_H
