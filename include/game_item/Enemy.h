// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Box.h"

class Enemy : public Box {
public:
    Enemy();
    bool Push(const glm::vec2& direction) override; // 覆寫推動邏輯
};

#endif