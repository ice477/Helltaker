#include "Box.h"

constexpr int TILE_SIZE = 75;


Box::Box(int index) : m_Index(index) {
    m_Animation = std::make_shared<Util::Animation>(
        std::vector<std::string>{"../assets/Texture2D/boxExport0001.png", "../assets/Texture2D/boxExport0002.png", "../assets/Texture2D/boxExport0003.png",
                                 "../assets/Texture2D/boxExport0004.png", "../assets/Texture2D/boxExport0005.png", "../assets/Texture2D/boxExport0006.png",
                                 "../assets/Texture2D/boxExport0007.png", "../assets/Texture2D/boxExport0008.png", "../assets/Texture2D/boxExport0009.png",
                                 "../assets/Texture2D/boxExport0010.png", "../assets/Texture2D/boxExport0011.png",
        },
        false, 50, false, 100);
    m_Transform.scale = {0.75f, 0.75f};
    SetDrawable(m_Animation);
    SetZIndex(5);
}

void Box::Update(std::vector<std::vector<int>>& m_MapData) {
    int count = 0;
    for (int y = 0; y < m_MapData.size(); ++y) {
        for (int x = 0; x < m_MapData[y].size(); ++x) {
            if (m_MapData[y][x] == 3) { // 3 代表 box
                if (count == m_Index) {
                    m_Transform.translation.x = m_OffsetX + x * TILE_SIZE;
                    m_Transform.translation.y = m_OffsetY + (static_cast<int>(m_MapData.size()) - 1 - y) * TILE_SIZE;
                    return;
                }
                ++count;
            }
        }
    }
    SetVisible(false);
}