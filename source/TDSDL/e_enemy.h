#ifndef E_ENEMY_H
#define E_ENEMY_H

#include "entity.h"
#include "map.h"
#include <QList>

class e_Enemy : public Entity
{
private:
    int type;
    QList<QPoint> route;
public:
    e_Enemy();

    void setRoute(QList<QPoint> route);
    void move(Map map);
};

#endif // E_ENEMY_H
