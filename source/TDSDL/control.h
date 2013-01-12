#ifndef CONTROL_H
#define CONTROL_H

#include "resources.h";
#include <QMap>
#include <QObject>
#include "SFML/Window/Event.hpp"

class Control : public QObject
{
    Q_OBJECT

public:
    Control();
    ~Control();
    void doControl(sf::Event *event);

signals:
    void moveCamera(bool up, bool down, bool left, bool right);
    void end();

};

#endif // CONTROL_H
