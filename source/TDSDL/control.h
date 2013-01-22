#ifndef CONTROL_H
#define CONTROL_H

#include "resources.h";
#include <QMap>
#include <QObject>
#include "SFML/Window/Event.hpp"
#include "unit.h"

class Control : public QObject
{
    Q_OBJECT

public:
    Control();
    ~Control();
    void doControl(sf::Event *event);

signals:
    void setCamControl(int state);
   // void setEntControl(int state);
    void setEntControl(Unit::ORDER order);
    void end();

};

#endif // CONTROL_H
