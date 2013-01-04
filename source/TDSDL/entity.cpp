#include "entity.h"

Entity::Entity(Sprite* sprite, int x, int y, int state)
{
    this->sprite = sprite;
    this->x      = x;
    this->y      = y;
    this->state  = state;
}

Entity::Entity()
{
    this->sprite = NULL;
    this->x      = 0;
    this->y      = 0;
    this->state  = 0;
}

Entity::~Entity()
{
    if (this->sprite != NULL)
        delete this->sprite;
}

void Entity::setSprite(Sprite* sprite)
{
    this->sprite = sprite;
}

void Entity::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
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
    this->state = state;
}

int Entity::getState()
{
    return this->state;
}

void Entity::refresh(SDL_Surface *dest)
{
    this->sprite->Draw(dest,x,y);
}
