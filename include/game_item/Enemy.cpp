// Enemy.cpp
#include "Enemy.h"

Enemy::Enemy() {
    // 初始化 Enemy 的屬性
    SetZIndex(4);
}

bool Enemy::Push(const glm::vec2& direction) {
    if (CheckObstacle(direction)) {
        // 如果有障礙，摧毀自己
        SetVisible(false); // 或者加入摧毀邏輯
        return false;
    }
    return Box::Push(direction); // 否則執行普通推動邏輯
}