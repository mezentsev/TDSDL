#include "entity.h"
#include <QDebug>

Entity::Entity(Animation * default_anim, int x, int y, int w, int h)
{
    this->x      = x;
    this->y      = y;
    this->addAnim(default_anim, "default");
    this->setDefault();

    sf::IntRect rct;
    rct.left = 0;
    rct.top = 0;
    rct.height = h;
    rct.width = w;
    this->rect = rct;
}

Entity::~Entity()
{
    qDeleteAll(this->anim.begin(), this->anim.end());
}

Entity * Entity::setXY(float x, float y)
{
    this->x = x;
    this->y = y;
    if (!this->anim.contains(this->animName))
        this->setDefault();
    this->anim[this->animName]->getSprite()->setPosition(x, y);
    return this;
}

Entity * Entity::setHW(int h, int w)
{
    this->h = h;
    this->w = w;
    return this;
}

float Entity::getX()
{
    return this->x;
}

float Entity::getY()
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

sf::Sprite * Entity::refresh(sf::Time time)
{
    return this->animate(time);
}

bool Entity::addAnim(Animation *anim, QString name)
{
    this->anim[name] = new Animation(anim);
    return true;
}

bool Entity::setAnim(QString name)
{
    if (this->anim.contains(name))
    {
        this->animName = name;
        this->setXY(this->x, this->y);
        return true;
    }
    return false;
}

void Entity::setDefault()
{
    this->animName = "default";
}

sf::Sprite * Entity::animate(sf::Time time)
{
    if (!this->anim.contains(this->animName))
    {
        this->setDefault();
    }

    this->rect = this->anim[this->animName]->animate(time);
    this->anim[this->animName]->getSprite()->setTextureRect(this->rect);
    return this->anim[this->animName]->getSprite();
}
