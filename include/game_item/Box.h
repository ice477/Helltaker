#ifndef BOX_H
#define BOX_H

#include "../Util/GameObject.hpp"
#include "../Util/Animation.hpp"
#include "../pch.hpp"

class Box : public Util::GameObject {
public:
    Box();
    virtual void Update(); // 更新邏輯
    virtual bool Push(const glm::vec2& direction); // 推動邏輯

protected:
    bool CheckObstacle(const glm::vec2& direction); // 檢查是否有障礙物

private:
    std::shared_ptr<Util::Animation> m_Animation; // 動畫屬性
};

#endif