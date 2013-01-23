#include "entity.h"
#include <QDebug>

Entity::Entity(Animation * default_anim, int x, int y, int w, int h, b2World * world, Physics::B2_BODY_TYPE type, float SCALE)
{
    this->x      = x;
    this->y      = y;
    this->addAnim(default_anim, "default");
    this->setDefault();
    this->SCALE = SCALE;

    sf::IntRect rct;
    rct.left = 0;
    rct.top = 0;
    rct.height = h;
    rct.width = w;
    this->rect = rct;

    this->phys.setWorld(world);
    this->phys.setType(type);
    this->phys.setShape(x, y, w, h);
    this->phys.createBody((void *)(x*y*w*h+w+y+x+h));
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

Entity * Entity::setAngle(float angle)
{
    this->angle = angle;
    if (!this->anim.contains(this->animName))
        this->setDefault();
    this->anim[this->animName]->getSprite()->setRotation(angle);
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
    sf::Sprite * spr = this->animate(time);
    spr->setOrigin(spr->getTextureRect().width/2, spr->getTextureRect().height/2);
    return spr;
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
        this->anim[this->animName]->setCurFrame(0);
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
    sf::IntRect rct;
    rct = this->anim[this->animName]->animate(time);
    rct.width = this->rect.width;
    rct.height = this->rect.height;
    this->anim[this->animName]->getSprite()->setTextureRect(rct);
    return this->anim[this->animName]->getSprite();
}
