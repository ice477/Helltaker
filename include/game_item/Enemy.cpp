#include "Enemy.h"

constexpr int TILE_SIZE = 75;

Enemy::Enemy(int index) : Box(index) {
    m_Animation = std::make_shared<Util::Animation>(
        std::vector<std::string>{
            "../assets/Texture2D/assets100V20225.png", "../assets/Texture2D/assets100V20226.png", "../assets/Texture2D/assets100V20227.png", "../assets/Texture2D/assets100V20228.png",
            "../assets/Texture2D/assets100V20229.png", "../assets/Texture2D/assets100V20230.png", "../assets/Texture2D/assets100V20231.png", "../assets/Texture2D/assets100V20232.png",
            "../assets/Texture2D/assets100V20233.png", "../assets/Texture2D/assets100V20234.png", "../assets/Texture2D/assets100V20235.png", "../assets/Texture2D/assets100V20236.png"
        },
        true, 50, true, 100);
    m_Transform.scale = {0.75f, 0.75f};
    SetDrawable(m_Animation);
    m_Animation->SetFrameRange(0,11);
    SetZIndex(5);
}

void Enemy::Update(std::vector<std::vector<int>>& m_MapData) {
    int count = 0;
    for (int y = 0; y < m_MapData.size(); ++y) {
        for (int x = 0; x < m_MapData[y].size(); ++x) {
            if (m_MapData[y][x] == 4) { // 4 代表 enemy
                if (count == m_Index) {
                    m_Transform.translation.x = m_OffsetX + x * TILE_SIZE;
                    m_Transform.translation.y = m_OffsetY + (static_cast<int>(m_MapData.size()) - 1 - y) * TILE_SIZE;
                    SetVisible(true);
                    return;
                }
                ++count;
            }
        }
    }
    SetVisible(false);
}