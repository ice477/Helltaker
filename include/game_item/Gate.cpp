#include "Gate.h"

constexpr int TILE_SIZE = 75;
constexpr int OFFSET_X = -300;
constexpr int OFFSET_Y = -275;

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
            if (m_MapData[y][x] == 5) {
                if (count == m_Index) {
                    m_Transform.translation.x = OFFSET_X + x * TILE_SIZE;
                    m_Transform.translation.y = OFFSET_Y + (7 - y) * TILE_SIZE;
                    SetVisible(true);
                    return;
                }
                ++count;
            }
        }
    }
    SetVisible(false);
}