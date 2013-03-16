#include "contactlistener.h"

#include <QDebug>

ContactListener::ContactListener()
{
}

void ContactListener::BeginContact(b2Contact *contact)
{
    Physics *phys = (Physics*)contact->GetFixtureA()->GetBody()->GetUserData();
    phys->begin(contact);
    phys = (Physics*)contact->GetFixtureB()->GetBody()->GetUserData();
    phys->begin(contact);
}

void ContactListener::EndContact(b2Contact *contact)
{
    Physics *phys = (Physics*)contact->GetFixtureA()->GetBody()->GetUserData();
    phys->end(contact);
    phys = (Physics*)contact->GetFixtureB()->GetBody()->GetUserData();
    phys->end(contact);
}
