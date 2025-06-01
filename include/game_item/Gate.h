// Gate.h
#ifndef GATE_H
#define GATE_H

#include "Box.h"

class Gate : public Box {
public:
    Gate(int index);
    void Update(std::vector<std::vector<int>>& m_MapData) override;

private:
    std::shared_ptr<Util::Animation> m_Animation; // 檢查玩家是否有鑰匙
};

#endif