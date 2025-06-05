// Trap.h
#ifndef TRAP_H
#define TRAP_H
#include "Box.h"

class Trap : public Box {
public:
    Trap(int index = 0);
    void Update(std::vector<std::vector<int>>& m_MapData);
    void SetOffset(int offsetX, int offsetY) {
        m_OffsetX = offsetX;
        m_OffsetY = offsetY;
    }
    int m_OffsetX;
    int m_OffsetY;
private:
    std::shared_ptr<Util::Animation> m_Animation;
};

#endif //TRAP_H