#ifndef APP_H
#define APP_H

#include <QObject>
#include <QDebug>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sprite.h"
#include "entity.h"
#include "resources.h"
#include "e_enemy.h"
#include "e_tower.h"
#include "e_ground.h"
#include "map.h"
#include "camera.h"

class App : public QObject{
private:
    bool running;
    SDL_Surface * screen;

    Resources<Sprite>    * _sprites;
    Resources<Entity>    * _entities;
    Resources<Animation> * _anims;
    Resources<e_Enemy>   * _enemies;
    Resources<e_Tower>   * _towers;
    Resources<e_Ground>  * _grounds;
    Map    *map;
    Camera *camera;

public:
    App();
    int Execute();

    bool Init();
    void Event(SDL_Event* event);
    void Loop();
    void Render();
    void Cleanup();

    void readMap(QString path);

public slots:
    void setValue(int value);
};

#endif // APP_H
