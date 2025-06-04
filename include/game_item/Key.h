//
// Created by sue bo  shuan on 25-4-18.
//

#ifndef KEY_H
#define KEY_H

#include "Box.h"

class Key : public Box {
public:
    Key(int index = 0);
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

#endif

