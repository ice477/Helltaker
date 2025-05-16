#ifndef HERO_H
#define HERO_H
#include "pch.hpp"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "game_item/MapManager.h"

class Hero : public Util::GameObject {
public:
    Hero(std::vector<std::vector<int>>& mapData);
    enum class State {
        DEFAULT,
        KICK,
        MOVE,
        WIN,
    };

    State m_State = State::DEFAULT;

    void Update();

private:
    int m_PosX;
    int m_PosY;
    std::vector<std::vector<int>>& m_MapData;
    std::shared_ptr<Util::Animation> m_Animation;

    struct Position {
        float x;
        float y;
    };
    Position m_TargetPosition;
};

#endif // HERO_H