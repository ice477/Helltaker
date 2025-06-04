#include "Gate.h"

constexpr int TILE_SIZE = 75;

Gate::Gate(int index) : Box(index) {
    m_Animation = std::make_shared<Util::Animation>(
        std::vector<std::string>{"../assets/Texture2D/backup_lockbox.png"},
        false, 50, false, 100);
    m_Transform.scale = {0.75f, 0.75f};
    SetDrawable(m_Animation);
    SetZIndex(5);
}

void Gate::Update(std::vector<std::vector<int>>& m_MapData) {
    int count = 0;
    for (int y = 0; y < m_MapData.size(); ++y) {
        for (int x = 0; x < m_MapData[y].size(); ++x) {
            if (m_MapData[y][x] == 5) { // 5 代表 gate
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