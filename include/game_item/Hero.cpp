// include/game_item/Hero.cpp
#include "Hero.h"
#include "Util/Input.hpp"
#include "spdlog/fmt/bundled/xchar.h"

#include <cmath>

constexpr int TILE_SIZE = 75;
constexpr int OFFSET_X = -300;
constexpr int OFFSET_Y = -275;

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
    m_PosX = static_cast<int>((m_Transform.translation.x - OFFSET_X) / TILE_SIZE);
    m_PosY = static_cast<int>((m_Transform.translation.y - OFFSET_Y) / TILE_SIZE) - 3;
}

void Hero::SetMapData(const std::vector<std::vector<int>>& mapData) {
    m_MapData = mapData;
    m_Initialized = false;
}

void Hero::Update(std::vector<std::vector<int>>& m_MapData) {
    fmt::print("m_PosX: {}, m_PosY: {},next_step_state: {}\n", m_PosX, m_PosY,m_MapData[m_PosY][m_PosX]);
    if (!m_Initialized && !m_MapData.empty()) {
        // 這裡做初始化座標等動作
        m_PosX = static_cast<int>((m_Transform.translation.x - OFFSET_X) / TILE_SIZE);
        m_PosY = static_cast<int>((m_Transform.translation.y - OFFSET_Y) / TILE_SIZE) - 3;
        m_MapData[m_PosY][m_PosX] = 0;
        m_Initialized = true;
    }
    int nextX = m_PosX;
    int nextY = m_PosY;

    if (m_State != State::MOVE) {
        if (Util::Input::IsKeyDown(Util::Keycode::S)) {
            nextY += 1;
            if (m_MapData[nextY][m_PosX] == 0) {
                m_TargetPosition = {m_Transform.translation.x, m_Transform.translation.y - TILE_SIZE};
                m_State = State::MOVE;
                m_PosY = nextY;
                m_Animation->SetFrameRange(12, 17);
            }
            else if (m_MapData[nextY][m_PosX] == 3) {
                int boxNextY = nextY + 1;
                // 檢查箱子前方一格是否為空地
                if (m_MapData[boxNextY][m_PosX] == 0) {
                    // 推動箱子
                    m_MapData[boxNextY][m_PosX] = 3;
                    m_MapData[nextY][m_PosX] = 0;
                }
            }/*
            else if (m_MapData[m_PosY][m_PosX] == 4) {
                m_TargetPosition = {m_Transform.translation.x, m_Transform.translation.y - TILE_SIZE};
                m_State = State::MOVE;
                m_Animation->SetFrameRange(12, 17);
            }
            else if (m_MapData[m_PosY][m_PosX] == 5) {
                m_TargetPosition = {m_Transform.translation.x, m_Transform.translation.y - TILE_SIZE};
                m_State = State::MOVE;
                m_Animation->SetFrameRange(12, 17);
            }
            else if (m_MapData[m_PosY][m_PosX] == 6) {
                m_TargetPosition = {m_Transform.translation.x, m_Transform.translation.y - TILE_SIZE};
                m_State = State::MOVE;
                m_Animation->SetFrameRange(12, 17);
            }
            else if (m_MapData[m_PosY][m_PosX] == 7) {
                m_TargetPosition = {m_Transform.translation.x, m_Transform.translation.y - TILE_SIZE};
                m_State = State::MOVE;
                m_Animation->SetFrameRange(12, 17);
            }
            else if (m_MapData[m_PosY][m_PosX] == 8) {
                m_TargetPosition = {m_Transform.translation.x, m_Transform.translation.y - TILE_SIZE};
                m_State = State::MOVE;
                m_Animation->SetFrameRange(12, 17);
            }*/
            else {
                nextY -= 1;
            }

        } else if (Util::Input::IsKeyDown(Util::Keycode::W)) {
            m_PosY -= 1;
            if (m_MapData[m_PosY][m_PosX] == 0) {
                m_TargetPosition = {m_Transform.translation.x, m_Transform.translation.y + TILE_SIZE};
                m_State = State::MOVE;
                m_Animation->SetFrameRange(12, 17);
            } else {
                m_PosY += 1;
            }
        } else if (Util::Input::IsKeyDown(Util::Keycode::A)) {
            m_PosX -= 1;
            if (m_MapData[m_PosY][m_PosX] == 0) {
                m_TargetPosition = {m_Transform.translation.x - TILE_SIZE, m_Transform.translation.y};
                m_Transform.scale.x = -0.75f;
                m_State = State::MOVE;
                m_Animation->SetFrameRange(12, 17);
            } else {
                m_PosX += 1;
            }
        } else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
            m_PosX += 1;
            if (m_MapData[m_PosY][m_PosX] == 0) {
                m_TargetPosition = {m_Transform.translation.x + TILE_SIZE, m_Transform.translation.y};
                m_Transform.scale.x = 0.75f;
                m_State = State::MOVE;
                m_Animation->SetFrameRange(12, 17);
            } else {
                m_PosX -= 1;
            }
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
}