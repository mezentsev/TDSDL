#include "entity.h"
#include <QDebug>

/*Entity::Entity(sf::Sprite* sprite, int x, int y, int w, int h, int state)
{
    this->sprite = sprite;
    this->x      = x;
    this->y      = y;
    this->state  = state;
    this->animName = "";
    this->rect = sprite->GetSubRect();
}*/

Entity::Entity()
{
    this->sprite = new sf::Sprite;
    this->x      = 0;
    this->y      = 0;
    this->state  = 0;
    this->animName = "";
    this->moving.left  = false;
    this->moving.right = false;
    this->moving.up    = false;
    this->moving.down  = false;
    this->speed = 100;
}

Entity::~Entity()
{
    delete sprite;
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
    if (sprite)
        this->sprite->SetPosition(this->x,this->x);
    QMap<QString, Animation*>::iterator i;
    for (i = anim.begin(); i != anim.end(); ++i)
    {
        (*i)->getSprite()->SetPosition(x,y);
    }
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

void Entity::setMoving(bool up, bool down, bool left, bool right)
{
    if (up)    this->moving.up    = !this->moving.up;
    if (down)  this->moving.down  = !this->moving.down;
    if (left)  this->moving.left  = !this->moving.left;
    if (right) this->moving.right = !this->moving.right;
}

void Entity::refresh(sf::RenderWindow *screen)
{
    //screen->Draw(*sprite);
    //qDebug() << this->rect.Top;
    //this->animate()
    screen->Draw(*this->animate(screen));//->Draw(dest, &spriteXY, &destXY, this->_angle, this->_scale);
}

void Entity::move(float freq)
{
    if (this->moving.left)
    {
        this->setAnim("runLeft");
        //float x = _entities->getRes("enemy_Dragon")->getX() - 100 * freq;
    }
    if (this->moving.right)
    {
        this->setAnim("runRight");
        //float x = _entities->getRes("enemy_Dragon")->getX() - 100 * freq;
    }
    if (!(this->moving.up||this->moving.down||this->moving.left||this->moving.right))
        this->setAnim("stop");

 //   this->setXY(x,y);
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
    //Возвращает несуществующий спрайт в случае если анимация
    //не существует, и падает!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (this->anim.contains(this->animName))
    {
        //this->sprite = this->anim[this->animName]->getSprite();
        this->rect = this->anim[this->animName]->animate(screen);
        this->anim[this->animName]->getSprite()->SetSubRect(this->rect);
        return this->anim[this->animName]->getSprite();
    }
    return this->sprite;
}
