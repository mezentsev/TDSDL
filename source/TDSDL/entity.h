#ifndef ENTITY_H
#define ENTITY_H

#include "sprite.h"
#include "SDL/SDL.h"

class Entity
{
private:
    Sprite sprite;
    //Animation anim;
    int x,y;
    int state;
public:
    Entity(Sprite sprite, int x, int y, int state);
    Entity();
    ~Entity();

    void setSprite(Sprite sprite);
    void setCoordinates(int x, int y);
    int getX();
    int getY();
    void setState(int state);
    int getState();

    void refreshImage(SDL_Surface *dest);
};

#endif // ENTITY_H
