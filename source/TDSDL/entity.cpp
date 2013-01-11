#include "entity.h"
#include <QDebug>

Entity::Entity(sf::Sprite* sprite, int x, int y, int w, int h, int state)
{
    this->sprite = sprite;
    this->x      = x;
    this->y      = y;
    this->state  = state;
    this->animName = "";
    this->spriteX = 0;
    this->spriteY = 0;
    this->w       = w;
    this->h       = h;
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
    this->w       = 0;
    this->h       = 0;
}

Entity::~Entity()
{
    //if (this->sprite != NULL)
    //    delete this->sprite;
    //this->anim.clear(); //Простая очистка, деструктор вызывает класс ресурсов вручную
}

Entity *  Entity::setSprite(sf::Sprite* sprite)
{
    this->sprite = sprite;
    return this;
}

Entity * Entity::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
    return this;
}

Entity * Entity::setHW(int h, int w)
{
    this->h = h;
    this->w = w;
    return this;
}

int Entity::getX()
{
    return this->x;
}

int Entity::getY()
{
    return this->y;
}

int Entity::getW()
{
    return this->w;
}

int Entity::getH()
{
    return this->h;
}

void Entity::setState(int state)
{
    this->state = state;
}

int Entity::getState()
{
    return this->state;
}

//Entity * Entity::setAngle(double angle)
//{
//    this->_angle = angle;
//    return this;
//}

//Entity * Entity::setScale(double scale)
//{
//    this->_scale = scale;
//    return this;
//}

void Entity::refresh(sf::RenderWindow *screen)
{
    screen->Draw(*sprite);
//    SDL_Rect destXY;
//    destXY.x = this->x;
//    destXY.y = this->y;

//    SDL_Rect spriteXY;
//    spriteXY.x = 0;
//    spriteXY.y = this->spriteY;
//    spriteXY.h = this->h;
//    spriteXY.w = this->w;

    //qDebug() << spriteXY.y;
  //  this->animate()->Draw(dest, &spriteXY, &destXY, this->_angle, this->_scale);
}

//bool Entity::addAnim(Animation *anim, QString name)
//{
//    this->anim[name] = anim;
//    return true;
//}

//Entity * Entity::setAnim(QString name)
//{
//    this->animName = name;
//    return this;
//}

//Sprite * Entity::animate()
//{
//    if (this->anim.contains(this->animName))
//    {
//        SDL_Rect rct = this->anim[this->animName]->animate();
//        //this->sprite = this->anim[this->animName]->getSprite();
//        this->spriteX = rct.x;
//        this->spriteY = rct.y;
//        return this->anim[this->animName]->getSprite();
//    }
//    return this->sprite;
//}
