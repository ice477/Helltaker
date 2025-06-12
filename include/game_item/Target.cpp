//
// Created by 蘇柏瑄 on 2025/6/6.
//

#include "Target.h"


constexpr int TILE_SIZE = 75;

Target::Target(int index, int level) : Box(index) {
    m_Animation = std::make_shared<Util::Animation>(
        std::vector<std::string>{
            "../assets/Texture2D/pandemonica_finalModel0001.png", "../assets/Texture2D/pandemonica_finalModel0002.png", "../assets/Texture2D/pandemonica_finalModel0003.png", "../assets/Texture2D/pandemonica_finalModel0004.png",
            "../assets/Texture2D/pandemonica_finalModel0005.png", "../assets/Texture2D/pandemonica_finalModel0006.png", "../assets/Texture2D/pandemonica_finalModel0007.png", "../assets/Texture2D/pandemonica_finalModel0008.png",
            "../assets/Texture2D/pandemonica_finalModel0009.png", "../assets/Texture2D/pandemonica_finalModel0010.png", "../assets/Texture2D/pandemonica_finalModel0011.png", "../assets/Texture2D/pandemonica_finalModel0012.png",

            "../assets/Texture2D/modeus_finalModel0001.png", "../assets/Texture2D/modeus_finalModel0002.png", "../assets/Texture2D/modeus_finalModel0003.png", "../assets/Texture2D/modeus_finalModel0004.png",
            "../assets/Texture2D/modeus_finalModel0005.png", "../assets/Texture2D/modeus_finalModel0006.png", "../assets/Texture2D/modeus_finalModel0007.png", "../assets/Texture2D/modeus_finalModel0008.png",
            "../assets/Texture2D/modeus_finalModel0009.png", "../assets/Texture2D/modeus_finalModel0010.png", "../assets/Texture2D/modeus_finalModel0011.png", "../assets/Texture2D/modeus_finalModel0012.png",

            "../assets/Texture2D/cerberus_finalModel0001.png", "../assets/Texture2D/cerberus_finalModel0002.png", "../assets/Texture2D/cerberus_finalModel0003.png", "../assets/Texture2D/cerberus_finalModel0004.png",
            "../assets/Texture2D/cerberus_finalModel0005.png", "../assets/Texture2D/cerberus_finalModel0006.png", "../assets/Texture2D/cerberus_finalModel0007.png", "../assets/Texture2D/cerberus_finalModel0008.png",
            "../assets/Texture2D/cerberus_finalModel0009.png", "../assets/Texture2D/cerberus_finalModel0010.png", "../assets/Texture2D/cerberus_finalModel0011.png", "../assets/Texture2D/cerberus_finalModel0012.png",

            "../assets/Texture2D/malina_finalModel0001.png", "../assets/Texture2D/malina_finalModel0002.png", "../assets/Texture2D/malina_finalModel0003.png", "../assets/Texture2D/malina_finalModel0004.png",
            "../assets/Texture2D/malina_finalModel0005.png", "../assets/Texture2D/malina_finalModel0006.png", "../assets/Texture2D/malina_finalModel0007.png", "../assets/Texture2D/malina_finalModel0008.png",
            "../assets/Texture2D/malina_finalModel0009.png", "../assets/Texture2D/malina_finalModel0010.png", "../assets/Texture2D/malina_finalModel0011.png", "../assets/Texture2D/malina_finalModel0012.png",

            "../assets/Texture2D/zdrada_finalModel0001.png", "../assets/Texture2D/zdrada_finalModel0002.png", "../assets/Texture2D/zdrada_finalModel0003.png", "../assets/Texture2D/zdrada_finalModel0004.png",
            "../assets/Texture2D/zdrada_finalModel0005.png", "../assets/Texture2D/zdrada_finalModel0006.png", "../assets/Texture2D/zdrada_finalModel0007.png", "../assets/Texture2D/zdrada_finalModel0008.png",
            "../assets/Texture2D/zdrada_finalModel0009.png", "../assets/Texture2D/zdrada_finalModel0010.png", "../assets/Texture2D/zdrada_finalModel0011.png", "../assets/Texture2D/zdrada_finalModel0012.png",

            "../assets/Texture2D/azazel_finalModel0001.png", "../assets/Texture2D/azazel_finalModel0002.png", "../assets/Texture2D/azazel_finalModel0003.png", "../assets/Texture2D/azazel_finalModel0004.png",
            "../assets/Texture2D/azazel_finalModel0005.png", "../assets/Texture2D/azazel_finalModel0006.png", "../assets/Texture2D/azazel_finalModel0007.png", "../assets/Texture2D/azazel_finalModel0008.png",
            "../assets/Texture2D/azazel_finalModel0009.png", "../assets/Texture2D/azazel_finalModel0010.png", "../assets/Texture2D/azazel_finalModel0011.png", "../assets/Texture2D/azazel_finalModel0012.png",

        },
        true, 50, true, 100);
    m_Transform.scale = {0.75f, 0.75f};
    SetDrawable(m_Animation);
    if (level == 1) {
        m_Animation->SetFrameRange(0,11);
    }
    else if (level == 2) {
        m_Animation->SetFrameRange(12,23);
    }
    else if (level == 3) {
        m_Animation->SetFrameRange(24,35);
    }
    else if (level == 4) {
        m_Animation->SetFrameRange(36,47);
    }
    else if (level == 5) {
        m_Animation->SetFrameRange(48,59);
    }
    else if (level == 6) {
        m_Animation->SetFrameRange(60,71);
    }
    SetZIndex(5);
}


void Target::Update(std::vector<std::vector<int>>& m_MapData) {
    int count = 0;
    for (int y = 0; y < m_MapData.size(); ++y) {
        for (int x = 0; x < m_MapData[y].size(); ++x) {
            if (m_MapData[y][x] == 8) {
                if (count == m_Index) {
                    m_Transform.translation.x = m_OffsetX + x * TILE_SIZE;
                    m_Transform.translation.y = m_OffsetY + (static_cast<int>(m_MapData.size()) - 1 - y) * TILE_SIZE + 30;
                    SetVisible(true);
                    return;
                }
                ++count;
            }
        }
    }
    SetVisible(false);
}