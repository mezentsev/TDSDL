#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>
#include <QObject>
#include "physics.h"

class ContactListener : public b2ContactListener//, public QObject
{
   // Q_OBJECT

public:
    ContactListener();

    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);

//signals:
 //   void beginContact(b2Contact *contact);
};

#endif // CONTACTLISTENER_H
