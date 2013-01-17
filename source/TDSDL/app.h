#ifndef APP_H
#define APP_H

#include <QObject>
#include <QDebug>
#include "entity.h"
#include "resources.h"
//#include "e_enemy.h"
//#include "e_tower.h"
//#include "e_ground.h"
#include "map.h"
#include "control.h"
#include "unit.h"
#include <QFile>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "cxxabi.h"

class App : public QObject
{
    Q_OBJECT

private:
    sf::RenderWindow *screen;
    sf::View *mainCamera;

    Resources<sf::Texture> * _textures;
    Resources<sf::Sprite>  * _sprites;
    Resources<Entity>      * _entities;
    Resources<Animation>   * _anims;
    Resources<Map>         * _maps;
    Resources<sf::View>    * _cameras;
//    Resources<sf::Text>       * _texts;
    Control *control;
    sf::Clock clock;
    sf::Time freq;

public:
    App();

    int Execute();

    bool Init();
    bool Load();
    void Event(sf::Event *event);
    void Loop();
    void Render();
    void Cleanup();
//    void readMap(QString path);

public slots:
    void Close();
};

#endif // APP_H
