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

    bool m_PassedLevel = false;
    bool PassedLevel() const { return m_PassedLevel; }

    State m_State = State::DEFAULT;


    void SetMapData(const std::vector<std::vector<int>>& mapData, int offsetX, int offsetY);

    bool Update(std::vector<std::vector<int>>& m_MapData);

    bool TryMove(int dx, int dy, std::vector<std::vector<int>>& map);

    void SetHasKey(bool hasKey) { m_HasKey = hasKey; };

    void SetOffset(int x, int y) { m_OffsetX = x; m_OffsetY = y; }

private:
    bool m_HasKey = false;

    int m_OffsetX = 0;
    int m_OffsetY = 0;

    int m_PosX;
    int m_PosY;

    bool m_ReachedTarget = false;

    bool m_Initialized = false;
    std::vector<std::vector<int>> m_MapData;

    std::shared_ptr<Util::Animation> m_Animation;

    struct Position {
        float x;
        float y;
    };
    Position m_TargetPosition;
};

#endif // HERO_H