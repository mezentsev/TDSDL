#include "entity.h"
#include <QDebug>

Entity::Entity(Animation * default_anim, int x, int y, sf::ConvexShape shape, b2World * world, Physics::B2_BODY_TYPE type, float SCALE)
{
    this->x      = x;
    this->y      = y;
    this->addAnim(default_anim, "default");
    this->setDefault();
    this->SCALE = SCALE;

    this->polygon = shape;

    this->phys.setWorld(world);
    this->phys.setType(type);
    this->phys.setShape(x, y, 64, 64, shape);
    this->phys.createBody((void *)(x*y*world->GetBodyCount()+y+x+world->GetBodyCount()));
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
    this->polygon.setPosition(x, y);
    return this;
}

Entity * Entity::setAngle(float angle)
{
    this->angle = angle;
    if (!this->anim.contains(this->animName))
        this->setDefault();
    this->polygon.setRotation(angle);
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

sf::ConvexShape Entity::refresh(sf::Time time)
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

sf::ConvexShape Entity::animate(sf::Time time)
{
    if (!this->anim.contains(this->animName))
    {
        this->setDefault();
    }

    // Окно кадра
    sf::IntRect rct;
    rct = this->anim[this->animName]->animate(time);

    const sf::Texture * tt = this->anim[this->animName]->getSprite()->getTexture();

    //Зададим окно текстуры полигону
    this->polygon.setTexture(tt);
    this->polygon.setTextureRect(rct);

    return this->polygon;
}

void Entity::doPhysics(float scale)
{
    b2Body * body = this->phys.getpHbody();

    float newX = body->GetPosition().x * scale;
    float newY = body->GetPosition().y * scale;
    float newAngle = remainder(body->GetAngle()*180/b2_pi,360.f);
    this->setXY(newX, newY);
    this->setAngle(newAngle);
}


