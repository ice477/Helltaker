#ifndef BOX_H
#define BOX_H

#include "../Util/GameObject.hpp"
#include "../Util/Animation.hpp"
#include "../pch.hpp"

class Box : public Util::GameObject {
public:
    Box();
    void Update(); // 更新邏輯

private:
    std::shared_ptr<Util::Animation> m_Animation; // 動畫屬性
};

#endif