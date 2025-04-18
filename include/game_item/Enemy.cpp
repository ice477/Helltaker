// Enemy.cpp
#include "Enemy.h"

Enemy::Enemy() {
    m_Animation = std::make_shared<Util::Animation>(
    std::vector<std::string>{
        "../assets/Texture2D/assets100V20225.png", "../assets/Texture2D/assets100V20226.png", "../assets/Texture2D/assets100V20227.png", "../assets/Texture2D/assets100V20228.png",
        "../assets/Texture2D/assets100V20229.png", "../assets/Texture2D/assets100V20230.png", "../assets/Texture2D/assets100V20231.png", "../assets/Texture2D/assets100V20232.png",
        "../assets/Texture2D/assets100V20233.png", "../assets/Texture2D/assets100V20234.png", "../assets/Texture2D/assets100V20235.png", "../assets/Texture2D/assets100V20236.png"
    },
        true, 50, true, 100);
    m_Transform.scale = {0.75f, 0.75f};
    m_Transform.translation = {75 ,-50};
    SetDrawable(m_Animation);
    m_Animation->SetFrameRange(0,11);
    SetZIndex(5);
}

void Enemy::Update() {
    // 更新動畫
    if (m_Animation) {
        m_Animation->Play();
    }
}