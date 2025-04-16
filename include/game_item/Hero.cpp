#include "Hero.h"
#include "Util/Input.hpp"
#include <cmath>



Hero::Hero()
    : m_Animation(std::make_shared<Util::Animation>(
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
          true, 50, true, 100)) {
    m_Transform.scale = {0.75f, 0.75f};
    m_Transform.translation = {0 ,100};
    SetDrawable(m_Animation);
    m_Animation->SetFrameRange(0,11);
    SetZIndex(5);
    m_State = State::DEFAULT;
}


void Hero::Update() {
    //移動邏輯
    if (m_State != State::MOVE) {
        if (Util::Input::IsKeyDown(Util::Keycode::S)) {
            m_TargetPosition = {m_Transform.translation.x, m_Transform.translation.y - 75};
            m_State = State::MOVE;
            m_Animation->SetFrameRange(12, 17); // 設置 MOVE 動畫範圍
        } else if (Util::Input::IsKeyDown(Util::Keycode::W)) {
            m_TargetPosition = {m_Transform.translation.x, m_Transform.translation.y + 75};
            m_State = State::MOVE;
            m_Animation->SetFrameRange(12, 17);
        } else if (Util::Input::IsKeyDown(Util::Keycode::A)) {
            m_TargetPosition = {m_Transform.translation.x - 75, m_Transform.translation.y};
            m_Transform.scale.x = -0.75f;
            m_State = State::MOVE;
            m_Animation->SetFrameRange(12, 17);
        } else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
            m_TargetPosition = {m_Transform.translation.x + 75, m_Transform.translation.y};
            m_Transform.scale.x = 0.75f;
            m_State = State::MOVE;
            m_Animation->SetFrameRange(12, 17);
        }
    }

    // 平滑移動邏輯
    if (m_State == State::MOVE) {
        float speed = 750.0f; // 每秒移動的距離
        float deltaTime = 1.0f / 60.0f; // 假設每幀 1/60 秒
        float step = speed * deltaTime;

        // 計算新的位置
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

        // 檢查是否到達目標位置
        if (m_Transform.translation.x == m_TargetPosition.x && m_Transform.translation.y == m_TargetPosition.y) {
            m_State = State::DEFAULT;
            m_Animation->SetFrameRange(0, 11); // 恢復 DEFAULT 動畫範圍
        }
    }
}

void Hero::Initialize(MapManager& mapMgr) {
    auto p = mapMgr.GetPlayerInitialPosition();
    m_PosX = p.first;
    m_PosY = p.second;
}

void Hero::Move(int dx, int dy, MapManager& mapMgr) {
    int newX = m_PosX + dx;
    int newY = m_PosY + dy;
    if (mapMgr.CanMove(newX, newY)) {
        m_PosX = newX;
        m_PosY = newY;
    }
}