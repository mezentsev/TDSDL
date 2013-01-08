#ifndef E_GROUND_H
#define E_GROUND_H

#include "entity.h"

class e_Ground : public Entity
{
private:
    int type;

public:    
    e_Ground();
    void setType(int);
    int getType();
};

#endif // E_GROUND_H
