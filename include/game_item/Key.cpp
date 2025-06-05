#include "Key.h"
#include "Key.h"

constexpr int TILE_SIZE = 75;


Key::Key(int index) : Box(index) {
    m_Animation = std::make_shared<Util::Animation>(
    std::vector<std::string>{
        "../assets/Texture2D/assets100V20104.png", "../assets/Texture2D/assets100V20105.png", "../assets/Texture2D/assets100V20106.png", "../assets/Texture2D/assets100V20107.png",
        "../assets/Texture2D/assets100V20108.png", "../assets/Texture2D/assets100V20109.png", "../assets/Texture2D/assets100V20110.png", "../assets/Texture2D/assets100V20111.png",
        "../assets/Texture2D/assets100V20112.png", "../assets/Texture2D/assets100V20113.png", "../assets/Texture2D/assets100V20114.png", "../assets/Texture2D/assets100V20115.png"
    },
        false, 50, true, 100);
    m_Transform.scale = {0.75f, 0.75f};
    SetDrawable(m_Animation);
    m_Animation->SetFrameRange(0,11);
    SetZIndex(5);
}

void Key::Update(std::vector<std::vector<int>>& m_MapData) {
    int count = 0;
    for (int y = 0; y < m_MapData.size(); ++y) {
        for (int x = 0; x < m_MapData[y].size(); ++x) {
            if (m_MapData[y][x] == 6) {
                m_Animation->Play();
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