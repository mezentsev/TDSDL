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

void Physics::setShape(float x, float y, float w, float h, b2PolygonShape shape)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->shape = shape;
}

void Physics::setShape(float x, float y, float w, float h, sf::ConvexShape shape)
{
    b2PolygonShape tob2shape;
    b2Vec2 verts[shape.getPointCount()];
    for(int i = 0; i < shape.getPointCount(); ++i)
        // TODO: 30.f -> SCALE
        verts[i] = b2Vec2(shape.getPoint(i).x/30.f, shape.getPoint(i).y/30.f);

    tob2shape.Set(verts, shape.getPointCount());
    this->setShape(x,y,w,h,tob2shape);
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
{//this->pHbody->GetContactList()->contact->IsTouching();
    return this->pHbody->GetContactList();
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

    //b2PolygonShape Shape;
    //Shape.SetAsBox((this->w/2.f)/SCALE, (this->h/2.f)/SCALE, b2Vec2((this->w/2.f)/SCALE,(this->h/2.f)/SCALE),0.f);

    b2FixtureDef FixtureDef;
    FixtureDef.density = this->density;
    FixtureDef.friction = this->friction;
    FixtureDef.shape = &this->shape;
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
