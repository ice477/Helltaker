// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Box.h"

class Enemy : public Box {
public:
    Enemy();
    void Update();
private:
    std::shared_ptr<Util::Animation> m_Animation;

};

#endif