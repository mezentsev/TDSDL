#include "entity.h"
#include <QDebug>

Entity::Entity(Sprite* sprite, int x, int y, int state)
{
    this->sprite = sprite;
    this->x      = x;
    this->y      = y;
    this->state  = state;
    this->animName = "";
    this->spriteX = 0;
    this->spriteY = 0;
}

Entity::Entity()
{
    this->sprite = NULL;
    this->x      = 0;
    this->y      = 0;
    this->state  = 0;
    this->animName = "";
    this->spriteX = 0;
    this->spriteY = 0;
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
    SDL_Rect destXY;
    destXY.x = this->x;
    destXY.y = this->y;

    SDL_Rect spriteXY;
    spriteXY.x = this->spriteX;
    spriteXY.y = this->spriteY;

    this->sprite->Draw(dest, spriteXY, destXY);
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
        SDL_Rect* rct = this->anim[this->animName]->animate();
        this->sprite = this->anim[this->animName]->getSprite();
        this->spriteX = rct->x;
        //qDebug() << rct.y;
        this->spriteY = rct->y;
        return true;
    }
    return false;
}
