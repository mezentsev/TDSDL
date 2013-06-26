#ifndef CONTROL_H
#define CONTROL_H

#include "resources.h";
#include <QMap>
#include <QObject>
#include "SFML/Window/Event.hpp"
#include "unit.h"
#include "resources.h"

class Control : public QObject
{
    Q_OBJECT

public:
    Control();
    ~Control();
    void doControl(sf::Event *event);

signals:
    void setEntControl(Unit::ORDER order);
    void createGround(int x, int y);
    void end();
    void menu();


};

#endif // CONTROL_H
