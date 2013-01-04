#include "entity.h"

Entity::Entity(Sprite sprite, int x, int y, int state)
{
    this->sprite=sprite;
    this->x=x;
    this->y=y;
    this->state=state;
}

Entity::Entity()
{
}

Entity::~Entity()
{

}

void Entity::setSprite(Sprite sprite)
{
    this->sprite=sprite;
}

void Entity::setCoordinates(int x, int y)
{
    this->x=x;
    this->y=y;
}

int Entity::getX()
{
    return this->x;
}

int Entity::getY()
{
    return this->y;
}

void Entity::setState(int state)
{
    this->state=state;
}

int Entity::getState()
{
    return this->state;
}



void Entity::refreshImage(SDL_Surface *dest)
{
    sprite.Draw(dest,x,y);
}
