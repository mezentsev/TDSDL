#ifndef APP_H
#define APP_H

#include <QObject>
#include <QDebug>

#include "Entity/entity.h"
#include "resources.h"
#include "Entity/control.h"
#include "Entity/unit.h"
#include "Physics/contactlistener.h"

#include <QFile>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <LTBL/Light/LightSystem.h>
#include <LTBL/Light/Light_Point.h>

class App : public QObject
{
    Q_OBJECT

private:
    sf::RenderWindow *screen;
    sf::View *mainCamera;

    ltbl::LightSystem *lights;

    Resources<sf::Texture> * _textures;
    Resources<sf::Sprite>  * _sprites;
    Resources<Entity>      * _entities;
    Resources<Animation>   * _anims;
    Resources<Skeletal>    * _skeletal;
    Resources<sf::View>    * _cameras;
    Control *control;
    sf::Clock clock;
    sf::Time freq;

    b2World * world; // Этот мир
                     // Обычный мальчик
                     // Коробки
    ContactListener *listener;
    float SCALE;
    QString resPath;

public:
    App();

    enum STATE{MENU, PAUSE, GAME};

    int Execute();

    bool Init();
    bool saveRes(QByteArray&);
    QByteArray loadRes();
    bool Load();
    void Event(sf::Event *event);
    void Loop();
    void Render();
    void Cleanup();

public slots:
    void Close();
};

#endif // APP_H
