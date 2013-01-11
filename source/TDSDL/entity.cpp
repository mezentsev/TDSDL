#include "entity.h"
#include <QDebug>

Entity::Entity(sf::Sprite* sprite, int x, int y, int w, int h, int state)
{
    this->sprite = sprite;
    this->x      = x;
    this->y      = y;
    this->state  = state;
    this->animName = "";
    this->rect = sprite->GetSubRect();
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
    //this->anim.clear(); //Простая очистка, деструктор вызывает класс ресурсов вручную
}

//Entity *  Entity::setSprite(sf::Sprite* sprite)
//{
//    this->sprite = sprite;
//    this->rect = sprite->GetSubRect();
//    return this;
//}

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
    //screen->Draw(*sprite);
    //qDebug() << this->rect.Top;
    //this->animate()
    screen->Draw(*this->animate(screen));//->Draw(dest, &spriteXY, &destXY, this->_angle, this->_scale);
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

sf::Sprite * Entity::animate(sf::RenderWindow * screen)
{
    if (this->anim.contains(this->animName))
    {
        //this->sprite = this->anim[this->animName]->getSprite();
        this->rect = this->anim[this->animName]->animate(screen);
        this->anim[this->animName]->getSprite()->SetSubRect(this->rect);
        return this->anim[this->animName]->getSprite();
    }
    return this->sprite;
}
