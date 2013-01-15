#include "control.h"
#include <QDebug>

Control::Control()
{
}

Control::~Control()
{
}

void Control::doControl(sf::Event *event)
{
    switch (event->type)
    {
    case sf::Event::Closed:
    {
        end();
        break;
    }
    case sf::Event::KeyPressed:
    {
        if (event->key.code == sf::Keyboard::Up)    emit setCamControl(1);
        if (event->key.code == sf::Keyboard::Down)  emit setCamControl(3);
        if (event->key.code == sf::Keyboard::Left)  emit setCamControl(5);
        if (event->key.code == sf::Keyboard::Right) emit setCamControl(7);

        if (event->key.code == sf::Keyboard::Escape) emit end();
        if (event->key.code == sf::Keyboard::W) emit setEntControl(6);
        if (event->key.code == sf::Keyboard::A) emit setEntControl(2);
        if (event->key.code == sf::Keyboard::D) emit setEntControl(3);

        break;
    }
    case sf::Event::KeyReleased:
    {
        if (event->key.code == sf::Keyboard::A) emit setEntControl(0);
        if (event->key.code == sf::Keyboard::D) emit setEntControl(1);

        break;
    }
    case sf::Event::MouseWheelMoved:
    {
        break;
    }
    case sf::Event::MouseMoved:
    {
        break;
    }
    case sf::Event::MouseButtonPressed:
    {
        break;
    }
    case sf::Event::MouseButtonReleased:
    {
        break;
    }
    }
}
