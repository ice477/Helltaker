#ifndef BOX_H
#define BOX_H

#include "../Util/GameObject.hpp"
#include "../Util/Animation.hpp"
#include "../pch.hpp"

// Box.h
class Box : public Util::GameObject {
public:
    enum class State {
        DEFAULT,
        MOVE,
    };
    State m_State = State::DEFAULT;

    Box(int index = 0);
    virtual ~Box() = default;
    virtual void Update(std::vector<std::vector<int>>& m_MapData); // virtual

protected:
    int m_Index;
    std::shared_ptr<Util::Animation> m_Animation;
    struct Position {
        float x;
        float y;
    };
    Position m_TargetPosition;
};

#endif