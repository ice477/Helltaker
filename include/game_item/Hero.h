#ifndef HERO_H
#define HERO_H
#include "pch.hpp"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "game_item/MapManager.h"

class Hero : public Util::GameObject {
public:
    Hero();
    enum class State {
        DEFAULT,
        KICK,
        MOVE,
        WIN,
    };

    State m_State = State::DEFAULT;

    void Update();
    void Moving(bool walkable);
    void Initialize(MapManager& mapMgr);
    void Move(int dx, int dy, MapManager& mapMgr);


private:
    int m_PosX;  // 新增的成員變數
    int m_PosY;

    std::shared_ptr<Util::Animation> m_Animation;

    struct Position {
        float x;
        float y;
    };
    Position m_TargetPosition;

};
#endif // HERO_H