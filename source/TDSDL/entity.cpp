#include "entity.h"
#include <QDebug>

Entity::Entity(Animation * default_anim, int x, int y, int w, int h, int state)
{
    this->x      = x;
    this->y      = y;
    this->state  = state;
    this->addAnim(default_anim, "default");
    this->setDefault();

    sf::IntRect rct;
    rct.Left = 0;
    rct.Top = 0;
    rct.Bottom = h;
    rct.Right = w;
    this->rect = rct;
}

Entity::~Entity()
{
}

//Entity *  Entity::setSprite(sf::Sprite* sprite)
//{
//    this->sprite = sprite;
//    this->rect = sprite->GetSubRect();
//    return this;
//}

Entity * Entity::setXY(float x, float y)
{
    this->x = x;
    this->y = y;
//    QMap<QString, Animation*>::iterator i;
//    for (i = anim.begin(); i != anim.end(); ++i)
//    {
//        (*i)->getSprite()->SetPosition(x,y);
//    }
    if (!this->anim.contains(this->animName))
        this->setDefault();
    this->anim[this->animName]->getSprite()->SetPosition(x, y);
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
    this->anim[name] = new Animation(anim);
    //*this->anim[name] = *anim;
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

sf::Sprite * Entity::animate(sf::RenderWindow * screen)
{
    if (!this->anim.contains(this->animName))
    {
        this->setDefault();
    }

    this->rect = this->anim[this->animName]->animate(screen);
    this->anim[this->animName]->getSprite()->SetSubRect(this->rect);
    return this->anim[this->animName]->getSprite();
}
