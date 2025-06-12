// include/game_item/Hero.cpp
#include "Hero.h"
#include "Util/Input.hpp"
#include "spdlog/fmt/bundled/xchar.h"

#include <cmath>

constexpr int TILE_SIZE = 75;
constexpr int offsetX = -300;
constexpr int offsetY = -275;


Hero::Hero()
    :m_Animation(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              // DEFAULT
              "../assets/Texture2D/hero0022.png", "../assets/Texture2D/hero0023.png", "../assets/Texture2D/hero0024.png", "../assets/Texture2D/hero0025.png",
              "../assets/Texture2D/hero0026.png", "../assets/Texture2D/hero0027.png","../assets/Texture2D/hero0028.png", "../assets/Texture2D/hero0029.png",
              "../assets/Texture2D/hero0030.png", "../assets/Texture2D/hero0031.png","../assets/Texture2D/hero0032.png", "../assets/Texture2D/hero0033.png",
              // MOVE
              "../assets/Texture2D/assets100V20053.png", "../assets/Texture2D/assets100V20054.png", "../assets/Texture2D/assets100V20055.png", "../assets/Texture2D/assets100V20056.png",
              "../assets/Texture2D/assets100V20057.png", "../assets/Texture2D/assets100V20058.png",
              // KICK
              "../assets/Texture2D/hero0040.png", "../assets/Texture2D/hero0041.png", "../assets/Texture2D/hero0042.png", "../assets/Texture2D/hero0043.png",
              "../assets/Texture2D/hero0044.png", "../assets/Texture2D/hero0045.png", "../assets/Texture2D/hero0046.png", "../assets/Texture2D/hero0047.png",
              "../assets/Texture2D/hero0048.png", "../assets/Texture2D/hero0049.png", "../assets/Texture2D/hero0050.png", "../assets/Texture2D/hero0051.png",
              "../assets/Texture2D/hero0052.png",
              // WIN
                "../assets/Texture2D/hero0059.png", "../assets/Texture2D/hero0060.png", "../assets/Texture2D/hero0061.png", "../assets/Texture2D/hero0062.png",
                "../assets/Texture2D/hero0063.png", "../assets/Texture2D/hero0064.png", "../assets/Texture2D/hero0065.png", "../assets/Texture2D/hero0066.png",
                "../assets/Texture2D/hero0067.png", "../assets/Texture2D/hero0068.png", "../assets/Texture2D/hero0069.png", "../assets/Texture2D/hero0070.png",
                "../assets/Texture2D/hero0071.png", "../assets/Texture2D/hero0072.png", "../assets/Texture2D/hero0073.png", "../assets/Texture2D/hero0074.png",
                "../assets/Texture2D/hero0075.png", "../assets/Texture2D/hero0076.png", "../assets/Texture2D/hero0077.png",
              //death
                "../assets/Texture2D/death_P20001.png", "../assets/Texture2D/death_P20002.png", "../assets/Texture2D/death_P20003.png", "../assets/Texture2D/death_P20004.png",
                "../assets/Texture2D/death_P20005.png", "../assets/Texture2D/death_P20006.png", "../assets/Texture2D/death_P20007.png", "../assets/Texture2D/death_P20008.png",
                "../assets/Texture2D/death_P20009.png", "../assets/Texture2D/death_P20010.png", "../assets/Texture2D/death_P20011.png", "../assets/Texture2D/death_P20012.png",
                "../assets/Texture2D/death_P20013.png", "../assets/Texture2D/death_P20014.png", "../assets/Texture2D/death_P20015.png", "../assets/Texture2D/death_P20016.png",
                "../assets/Texture2D/death_P20017.png", "../assets/Texture2D/death_P20018.png",
          },
          true, 50, true, 100))
{
    m_Transform.scale = {0.75f, 0.75f};
    SetDrawable(m_Animation);
    m_Animation->SetFrameRange(0,11);
    SetZIndex(7);
    m_State = State::DEFAULT;
    // 初始化地圖座標
    m_PosX = static_cast<int>((m_Transform.translation.x - offsetX) / TILE_SIZE);
    m_PosY = static_cast<int>(m_MapData.size() - 1 - ((m_Transform.translation.y - offsetY) / TILE_SIZE));
}
void Hero::SetMapData(const std::vector<std::vector<int>>& mapData, int offsetX, int offsetY) {
    m_MapData = mapData;
    int mapHeight = static_cast<int>(m_MapData.size());
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < static_cast<int>(m_MapData[y].size()); ++x) {
            if (m_MapData[y][x] == 2) {
                m_PosX = x;
                m_PosY = y;
                m_Transform.translation.x = offsetX + x * TILE_SIZE;
                m_Transform.translation.y = offsetY + (mapHeight - 1 - y) * TILE_SIZE;
                m_OffsetX = offsetX;
                m_OffsetY = offsetY;
                m_Initialized = false;
                return;
            }
        }
    }
}

bool Hero::Update(std::vector<std::vector<int>>& m_MapData) {
    if (!m_Initialized && !m_MapData.empty()) {
        m_MapData[m_PosY][m_PosX] = 0;
        m_Initialized = true;
    }

    if (m_Animation->GetCurrentFrameIndex() ==17 || m_Animation->GetCurrentFrameIndex() == 23) {
        m_Animation->SetFrameRange(0,11);
    }else if (m_Animation->GetCurrentFrameIndex() == 66) {
        m_Animation->SetFrameRange(0,11);
        m_HeroDead = true;
    }

    if (m_State != State::MOVE  && !m_HeroDead) {
        if (Util::Input::IsKeyDown(Util::Keycode::W)) {
            m_Heromve =true;
            m_ReachedTarget = TryMove(0, -1, m_MapData);
        }
        if (Util::Input::IsKeyDown(Util::Keycode::S)) {
            m_Heromve =true;
            m_ReachedTarget = TryMove(0, 1, m_MapData);
        }
        if (Util::Input::IsKeyDown(Util::Keycode::A)) {
            m_Heromve =true;
            m_Transform.scale = {-0.75f, 0.75f};
            m_ReachedTarget = TryMove(-1, 0, m_MapData);
        }
        if (Util::Input::IsKeyDown(Util::Keycode::D)) {
            m_Heromve =true;
            m_Transform.scale = {0.75f, 0.75f};
            m_ReachedTarget = TryMove(1, 0, m_MapData);
        }

        if (m_Heromve) {
            m_Steps--;
            m_Heromve = false;
        }

        if (m_HeroDead && !m_DeadShift) {
            m_Transform.translation.y += 250;
            m_DeadShift = true;
        }else if (!m_HeroDead && m_DeadShift) {
            m_Transform.translation.y -= 250;
            m_DeadShift = false;
        }
    }

    // 平滑移動
    if (m_State == State::MOVE) {
        float speed = 750.0f;
        float deltaTime = 1.0f / 60.0f;
        float step = speed * deltaTime;

        if (std::abs(m_Transform.translation.x - m_TargetPosition.x) > step) {
            m_Transform.translation.x += (m_TargetPosition.x > m_Transform.translation.x ? step : -step);
        } else {
            m_Transform.translation.x = m_TargetPosition.x;
        }

        if (std::abs(m_Transform.translation.y - m_TargetPosition.y) > step) {
            m_Transform.translation.y += (m_TargetPosition.y > m_Transform.translation.y ? step : -step);
        } else {
            m_Transform.translation.y = m_TargetPosition.y;
        }

        if (m_Transform.translation.x == m_TargetPosition.x && m_Transform.translation.y == m_TargetPosition.y) {
            m_State = State::DEFAULT;
            m_Animation->SetFrameRange(0, 11);
        }
    }
    return m_ReachedTarget;
}

bool Hero::TryMove(int dx, int dy, std::vector<std::vector<int>>& map) {
    int nextX = m_PosX + dx;
    int nextY = m_PosY + dy;
    if (nextY < 0 || nextY >= (int)map.size() || nextX < 0 || nextX >= (int)map[0].size())
        return true;

    int target = map[nextY][nextX];
    // 空地


    if (m_Steps <= 0) {
        m_HeroDead = true;
        m_Animation->SetFrameRange(50,  66);
    }
    else if (target == 0) {
        m_TargetPosition = {m_Transform.translation.x + dx * TILE_SIZE, m_Transform.translation.y - dy * TILE_SIZE};
        m_State = State::MOVE;
        m_PosX = nextX;
        m_PosY = nextY;
        m_Animation->SetFrameRange(12, 17);
        return true;
    }
    // 箱子
    else if (target == 3) {
        m_Animation->SetFrameRange(18, 30);
        int boxNextX = nextX + dx;
        int boxNextY = nextY + dy;
        if (boxNextY >= 0 && boxNextY < (int)map.size() && boxNextX >= 0 && boxNextX < (int)map[0].size() && map[boxNextY][boxNextX] == 0) {
            map[boxNextY][boxNextX] = 3;
            map[nextY][nextX] = 0;
        }
        return true;
    }
    // 敵人
    else if (target == 4) {
        m_Animation->SetFrameRange(18, 23);
        int enemyNextX = nextX + dx;
        int enemyNextY = nextY + dy;
        if (enemyNextY >= 0 && enemyNextY < (int)map.size() && enemyNextX >= 0 && enemyNextX < (int)map[0].size() && map[enemyNextY][enemyNextX] == 0) {
            map[enemyNextY][enemyNextX] = 4;
            map[nextY][nextX] = 0;
        } else {
            map[nextY][nextX] = 0;
        }
        return true;
    }
    // 門
    else if (target == 5 && m_HasKey) {
        map[nextY][nextX] = 0;
        m_TargetPosition = {m_Transform.translation.x + dx * TILE_SIZE, m_Transform.translation.y - dy * TILE_SIZE};
        m_State = State::MOVE;
        m_PosX = nextX;
        m_PosY = nextY;
        m_Animation->SetFrameRange(12, 17);
        return true;
    }
    // 鑰匙
    else if (target == 6) {
        m_HasKey = true;
        map[nextY][nextX] = 0;
        m_TargetPosition = {m_Transform.translation.x + dx * TILE_SIZE, m_Transform.translation.y - dy * TILE_SIZE};
        m_State = State::MOVE;
        m_PosX = nextX;
        m_PosY = nextY;
        m_Animation->SetFrameRange(12, 17);
        return true;
    }
    // 目標
    else if (target == 7) {
        m_Animation->SetFrameRange(31,49);
        m_PassedLevel = true;
        return false;
    }
    // 陷阱
    else if (target == 8) {
        m_TargetPosition = {m_Transform.translation.x + dx * TILE_SIZE, m_Transform.translation.y - dy * TILE_SIZE};
        m_State = State::MOVE;
        m_PosX = nextX;
        m_PosY = nextY;
        m_Animation->SetFrameRange(12, 17);
        m_Steps--;
        return true;
    }else {
        m_Animation->SetFrameRange(12, 17);
    }
    return false;
}