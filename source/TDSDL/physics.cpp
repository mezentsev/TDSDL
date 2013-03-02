#include "physics.h"
#include <QDebug>

Physics::Physics()
{
    this->type = b2_dynamicBody;
    this->density = 2.f;
    this->friction = 1.f;
    this->curSpeed = 0.f;
    this->maxSpeed = 10.f;
    this->x = 0.f;
    this->y = 0.f;
    this->w = 0.f;
    this->h = 0.f;
    this->pHworld = NULL;
    this->pHbody = NULL;
}

Physics::~Physics()
{
}

void Physics::setWorld(b2World * world)
{
    this->pHworld = world;
}

b2Body * Physics::getpHbody()
{
    for (b2Body* BodyIterator = this->pHworld->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    {
        if (BodyIterator->GetUserData() == this->data)
        {
            return BodyIterator;
        }
    }

    return NULL;
}

void Physics::setShape(float x, float y, b2PolygonShape shape)
{
    this->x = x;
    this->y = y;
    this->shape.append(shape);
}

void Physics::setShape(float x, float y, sf::ConvexShape shape)
{
    b2PolygonShape tob2shape;
    b2Vec2 verts[shape.getPointCount()];
    for(int i = 0; i < shape.getPointCount(); ++i)
        // TODO: 30.f -> SCALE
        verts[i] = b2Vec2(shape.getPoint(i).x/30.f, shape.getPoint(i).y/30.f);

    tob2shape.Set(verts, shape.getPointCount());
    this->setShape(x,y,tob2shape);
}

QList<b2PolygonShape> &Physics::getShapeList()
{
    b2Fixture * fixtures = this->pHbody->GetFixtureList();
    this->shape.clear();
    while(fixtures != NULL)
    {
        b2PolygonShape poly = (b2PolygonShape&)*fixtures->GetShape();
        this->shape.append(poly);

        fixtures = fixtures->GetNext();
    }

    return this->shape;
}


void Physics::setType(B2_BODY_TYPE type)
{
    this->type = (b2BodyType)type;
}

float Physics::getGravity()
{
    return this->pHworld->GetGravity().y;
}

bool Physics::isContact()
{
    return this->getpHbody()->GetContactList();
}

void Physics::createBody(void * data, float SCALE)
{
    this->data = data;
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(this->x/SCALE, this->y/SCALE);
    BodyDef.type = this->type;
    BodyDef.fixedRotation = true;
    this->pHbody = this->pHworld->CreateBody(&BodyDef);
    this->pHbody->SetUserData(data);

    b2FixtureDef FixtureDef;
    if (!this->shape.isEmpty())
    {
        for (QList<b2PolygonShape>::iterator i = this->shape.begin(); i != this->shape.end(); i++)
        {
            FixtureDef.density = this->density;
            FixtureDef.friction = this->friction;
            FixtureDef.shape = &(*i);
            FixtureDef.restitution = 0;
            this->pHbody->CreateFixture(&FixtureDef);
        }
    }
}
