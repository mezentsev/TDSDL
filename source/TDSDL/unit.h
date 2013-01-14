#ifndef UNIT_H
#define UNIT_H

#include "entity.h"

class Unit : public Entity
{
    Q_OBJECT

private:
    int state; //Состояние объекта (возможно enum)
/*    0 - смотрит влево
      1 - смотрит вправо
      2 - двигается влево
      3 - двигается вправо
      4 - прыжок влево
      5 - прыжок вправо
      6 - прыжок вверх
      7 - казнь через повешение
*/

public:
    Unit(Animation *anim);

public slots:
    void setControl(int state);
    void setState(int state);
    int  getState();
};

#endif // UNIT_H
