//
// Created by 蘇柏瑄 on 2025/6/6.
//

#ifndef TARGET_H
#define TARGET_H

#include "Box.h"


class Target  : public Box {
public:
    Target(int index);
    void Update(std::vector<std::vector<int>>& m_MapData,int level);
    void SetOffset(int offsetX, int offsetY) {
        m_OffsetX = offsetX;
        m_OffsetY = offsetY;
    }
    int m_OffsetX;
    int m_OffsetY;

};



#endif //TARGET_H
