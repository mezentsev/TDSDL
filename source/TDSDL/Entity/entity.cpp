#include "entity.h"
#include <QDebug>

Entity::Entity(Animation * default_anim, int x, int y, sf::ConvexShape shape, QList<sf::ConvexShape> physShapes, b2World * world, Physics::B2_BODY_TYPE type, float SCALE)
{
    this->a_type = ANIM_TYPE::SPRITE;
    this->x      = x;
    this->y      = y;
    this->addAnim(default_anim, "default");
    this->setDefault();
    this->SCALE = SCALE;

    this->polygon = shape;

    setWorld(world);
    setType(type);

    QList<sf::ConvexShape>::iterator i;
    for(i = physShapes.begin(); i != physShapes.end(); i++)
    {
        this->phys.setShape(x, y, *i);
    }

    this->phys.createBody((void *)(x*y*world->GetBodyCount()+y+x+world->GetBodyCount()));
}

Entity::Entity(Animation * anim):
    x(0),
    y(0),
    a_type(ANIM_TYPE::SKELETAL),
    SCALE(1.0f)
{
    this->addAnim(anim);
    this->setDefault();
}

Entity::Entity(Skeletal * skeletal, b2World * world, Physics::B2_BODY_TYPE type):
    x(0),
    y(0),
    a_type(ANIM_TYPE::SKELETAL),
    SCALE(1.0f)
{
    this->addAnim(skeletal);
    this->setDefault();

    sf::ConvexShape shape(4);
    sf::Vector2u v = skeletal->getSize();
    shape.setPoint(0, sf::Vector2f(0,0));
    shape.setPoint(1, sf::Vector2f(v.x,0));
    shape.setPoint(2, sf::Vector2f(v.x,v.y));
    shape.setPoint(3, sf::Vector2f(0,v.y));
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1);

    setWorld(world);
    setType(type);

    QList<sf::ConvexShape> physShapes;
    physShapes.append(shape);
    QList<sf::ConvexShape>::iterator i;
    for(i = physShapes.begin(); i != physShapes.end(); i++)
    {
        this->phys.setShape(x, y, *i);
    }

    this->phys.createBody((void *)(world->GetBodyCount()+world->GetBodyCount()));
    //shape.setFillColor(sf::Color::Green);

    this->polygon = shape;
}

Entity::~Entity()
{
    qDeleteAll(this->anim.begin(), this->anim.end());
    qDeleteAll(this->skeletal.begin(), this->skeletal.end());
}

void Entity::setWorld(b2World * world)
{
    this->phys.setWorld(world);
}

void Entity::setType(Physics::B2_BODY_TYPE type)
{
    this->phys.setType(type);
}

Entity * Entity::setXY(float x, float y)
{
    this->x = x;
    this->y = y;
    if (!this->anim.contains(this->animName))
        this->setDefault();
    switch (this->a_type)
    {
    case ANIM_TYPE::SKELETAL:
    {
        //this->skeletal[this->animName]->setXY(x, y);
        break;
    }
    case ANIM_TYPE::SPRITE:
    default:
    {
        this->anim[this->animName]->getSprite()->setPosition(x, y);
        break;
    }
    }
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

QList< sf::ConvexShape > Entity::getPhysShapeList()
{
    b2Body * body = this->phys.getpHbody();

    float newX = body->GetPosition().x * 30.f;
    float newY = body->GetPosition().y * 30.f;

    // Отладочные линии по физическим границам
    QList< b2PolygonShape > b2shapes = this->phys.getShapeList();
    QList< sf::ConvexShape > shapes;
    foreach (b2PolygonShape b2shape, b2shapes) {
        sf::ConvexShape sh(b2shape.GetVertexCount());
        for(int i = 0; i < b2shape.GetVertexCount(); ++i)
            sh.setPoint(i, sf::Vector2f(b2shape.GetVertex(i).x * 30.f + newX, b2shape.GetVertex(i).y * 30.f + newY));
        sh.setOutlineColor(sf::Color::Green);
        sh.setOutlineThickness(1.f);
        sh.setFillColor(sf::Color::Transparent);
        shapes.append(sh);
    }

    return shapes;
}

bool Entity::addAnim(Animation *anim, QString name)
{
    this->anim[name] = new Animation(anim);
    return true;
}

bool Entity::addAnim(Skeletal * skeletal, QString name)
{
    this->skeletal[name] = new Skeletal(skeletal);
    return true;
}

bool Entity::setAnim(QString name)
{
    switch (this->a_type)
    {
    case ANIM_TYPE::SPRITE:
    {
        if (this->anim.contains(name))
        {
            this->animName = name;
            this->anim[this->animName]->setCurFrame(0);
            this->setXY(this->x, this->y);
            return true;
        }
        break;
    }
    case ANIM_TYPE::SKELETAL:
    {
        if (this->skeletal.contains(name))
        {
            this->animName = name;
            // TODO: смена анимации
            //this->anim[this->animName]->setCurFrame(0);
            this->setXY(this->x, this->y);
            return true;
        }
    }
    }


    return false;
}

void Entity::setDefault()
{
    this->animName = "default";
}

sf::ConvexShape Entity::animate(sf::Time time)
{
    switch(this->a_type)
    {
    case ANIM_TYPE::SPRITE:
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
        break;
    }
    case ANIM_TYPE::SKELETAL:
    {
        sf::Sprite texture(this->skeletal[this->animName]->animate(time)->getTexture());
        this->polygon.setTexture(texture.getTexture(), true);
        //this->polygon.setTextureRect(this->polygon.getTextureRect());

        return this->polygon;
        break;
    }
    }
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
