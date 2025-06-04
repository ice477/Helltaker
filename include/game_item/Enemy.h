// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Box.h"

class Enemy : public Box {
public:
    Enemy(int index);
    void Update(std::vector<std::vector<int>>& m_MapData) override;
    void SetOffset(int offsetX, int offsetY) {
        m_OffsetX = offsetX;
        m_OffsetY = offsetY;
    }
    int m_OffsetX;
    int m_OffsetY;

};

#endif