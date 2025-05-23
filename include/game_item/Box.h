#ifndef BOX_H
#define BOX_H

#include "../Util/GameObject.hpp"
#include "../Util/Animation.hpp"
#include "../pch.hpp"

class Box : public Util::GameObject {
public:
    enum class State {
        DEFAULT,
        MOVE,
    };
    State m_State = State::DEFAULT;


    Box();
    void Update(std::vector<std::vector<int>>& m_MapData); // 更新邏輯

private:
    std::shared_ptr<Util::Animation> m_Animation; // 動畫屬性

    struct Position {
        float x;
        float y;
    };
    Position m_TargetPosition;
};

#endif