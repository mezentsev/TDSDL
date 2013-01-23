#include "physics.h"
#include <QDebug>

Physics::Physics()
{
    this->type = b2_dynamicBody;
    this->density = 10.f;
    this->friction = 2.f;
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

void Physics::setShape(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void Physics::setType(B2_BODY_TYPE type)
{
    this->type = (b2BodyType)type;
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

    b2PolygonShape Shape;
    Shape.SetAsBox((this->w/2.f)/SCALE, (this->h/2.f)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = this->density;
    FixtureDef.friction = this->friction;
    FixtureDef.shape = &Shape;
    FixtureDef.restitution = 0;
    this->pHfixture = this->pHbody->CreateFixture(&FixtureDef);
}

//void CreateGround()
//{
//    b2BodyDef BodyDef;
//    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
//    BodyDef.angle = 0.3f;
//    BodyDef.type = b2_staticBody;
//    BodyDef.bullet = true;
//    b2Body* Body = World.CreateBody(&BodyDef);

//    b2PolygonShape Shape;
//    Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE);
//    b2FixtureDef FixtureDef;
//    FixtureDef.density = 0.f;
//    FixtureDef.shape = &Shape;
//    char * ch = "ground";
//    FixtureDef.userData = ch;
//    Body->CreateFixture(&FixtureDef);
//}
