// Gate.cpp
#include "Gate.h"

Gate::Gate() {
    // 初始化 Gate 的屬性
    SetZIndex(5);
}

bool Gate::Push(const glm::vec2& direction) {
    if (PlayerHasKey()) {
        SetVisible(false); // 消除 Gate
        return true;
    }
    return false; // 沒有鑰匙則無法推動
}

bool Gate::PlayerHasKey() {
    // 檢查玩家是否持有鑰匙
    // 這裡可以加入具體的檢測邏輯
    return true; // 假設玩家有鑰匙
}