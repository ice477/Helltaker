// Gate.h
#ifndef GATE_H
#define GATE_H

#include "Box.h"

class Gate : public Box {
public:
    Gate();
    bool Push(const glm::vec2& direction) override; // 覆寫推動邏輯

private:
    bool PlayerHasKey(); // 檢查玩家是否有鑰匙
};

#endif