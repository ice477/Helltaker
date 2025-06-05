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
              "../assets/Texture2D/hero0050.png", "../assets/Texture2D/hero0051.png", "../assets/Texture2D/hero0052.png", "../assets/Texture2D/hero0059.png",
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

    if (m_State != State::MOVE) {
        if (Util::Input::IsKeyDown(Util::Keycode::W))
            m_ReachedTarget = TryMove(0, -1, m_MapData);
        if (Util::Input::IsKeyDown(Util::Keycode::S))
            m_ReachedTarget = TryMove(0, 1, m_MapData);
        if (Util::Input::IsKeyDown(Util::Keycode::A)) {
            m_Transform.scale = {-0.75f, 0.75f};
            m_ReachedTarget = TryMove(-1, 0, m_MapData);
        }
        if (Util::Input::IsKeyDown(Util::Keycode::D)) {
            m_Transform.scale = {0.75f, 0.75f};
            m_ReachedTarget = TryMove(1, 0, m_MapData);
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
    if (target == 0) {
        m_TargetPosition = {m_Transform.translation.x + dx * TILE_SIZE, m_Transform.translation.y - dy * TILE_SIZE};
        m_State = State::MOVE;
        m_PosX = nextX;
        m_PosY = nextY;
        m_Animation->SetFrameRange(12, 17);
        return true;
    }
    // 箱子
    if (target == 3) {
        int boxNextX = nextX + dx;
        int boxNextY = nextY + dy;
        if (boxNextY >= 0 && boxNextY < (int)map.size() && boxNextX >= 0 && boxNextX < (int)map[0].size() && map[boxNextY][boxNextX] == 0) {
            map[boxNextY][boxNextX] = 3;
            map[nextY][nextX] = 0;
        }
        return true;
    }
    // 敵人
    if (target == 4) {
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
    if (target == 5 && m_HasKey) {
        map[nextY][nextX] = 0;
        m_TargetPosition = {m_Transform.translation.x + dx * TILE_SIZE, m_Transform.translation.y - dy * TILE_SIZE};
        m_State = State::MOVE;
        m_PosX = nextX;
        m_PosY = nextY;
        m_Animation->SetFrameRange(12, 17);
        return true;
    }
    // 鑰匙
    if (target == 6) {
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
    if (target == 7) {
        m_PassedLevel = true;
        return false;
    }
    // 陷阱
    if (target == 8) {
        m_TargetPosition = {m_Transform.translation.x + dx * TILE_SIZE, m_Transform.translation.y - dy * TILE_SIZE};
        m_State = State::MOVE;
        m_PosX = nextX;
        m_PosY = nextY;
        m_Animation->SetFrameRange(12, 17);
        return true;
    }
    return false;
}