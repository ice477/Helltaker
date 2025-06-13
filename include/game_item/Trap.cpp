#include "Trap.h"

constexpr int TILE_SIZE = 75;

Trap::Trap(int index) : Box(index) {
    m_Animation = std::make_shared<Util::Animation>(
        std::vector<std::string>{
            "../assets/Texture2D/assets100V20116.png","../assets/Texture2D/assets100V20117.png","../assets/Texture2D/assets100V20118.png","../assets/Texture2D/assets100V20119.png",
            "../assets/Texture2D/assets100V20120.png","../assets/Texture2D/assets100V20121.png","../assets/Texture2D/assets100V20122.png","../assets/Texture2D/assets100V20123.png"},
        true, 50, true, 100);
    m_Transform.scale = {0.75f, 0.75f};
    SetDrawable(m_Animation);
    m_Animation->SetFrameRange(0,7);
    SetZIndex(3);
}

void Trap::Update(std::vector<std::vector<int>>& m_MapData) {
    int count = 0;
    for (int y = 0; y < m_MapData.size(); ++y) {
        for (int x = 0; x < m_MapData[y].size(); ++x) {
            if (m_MapData[y][x] == 8) {
                m_Animation->Play();
                if (count == m_Index) {
                    m_Transform.translation.x = m_OffsetX + x * TILE_SIZE;
                    m_Transform.translation.y = m_OffsetY + (static_cast<int>(m_MapData.size()) - 1 - y) * TILE_SIZE + 30;
                    return;
                }
                ++count;
            }
        }
    }
    SetVisible(false);
}