#include "entity.h"

Entity::Entity(Sprite* sprite, int x, int y, int state)
{
    this->sprite = sprite;
    this->x      = x;
    this->y      = y;
    this->state  = state;
    this->animName = "";
}

Entity::Entity()
{
    this->sprite = NULL;
    this->x      = 0;
    this->y      = 0;
    this->state  = 0;
    this->animName = "";
}

Entity::~Entity()
{
    //if (this->sprite != NULL)
    //    delete this->sprite;
    this->anim.clear(); //Простая очистка, деструктор вызывает класс ресурсов вручную
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
    this->animate();
    this->anim[this->name]->animate()->Draw();
    this->sprite->Draw(dest,x,y);
}

bool Entity::addAnim(Animation *anim, QString name)
{
    this->anim[name] = anim;
    return true;
}

Entity * Entity::setAnim(QString name)
{
    this->animName = name;
    return this;
}

bool Entity::animate()
{
    if (this->anim.contains(this->animName))
    {
        this->anim[this->animName]->animate();
        return true;
    }
    return false;
}
