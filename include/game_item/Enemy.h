// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Box.h"

class Enemy : public Box {
public:
    Enemy(int index);
    void Update(std::vector<std::vector<int>>& m_MapData) override;

};

#endif