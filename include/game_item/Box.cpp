#include "Box.h"

Box::Box() {
    m_Animation = std::make_shared<Util::Animation>(
        std::vector<std::string>{"../assets/Texture2D/boxExport0001.png", "../assets/Texture2D/boxExport0002.png", "../assets/Texture2D/boxExport0003.png",
                                 "../assets/Texture2D/boxExport0004.png", "../assets/Texture2D/boxExport0005.png", "../assets/Texture2D/boxExport0006.png",
                                 "../assets/Texture2D/boxExport0007.png", "../assets/Texture2D/boxExport0008.png", "../assets/Texture2D/boxExport0009.png",
                                 "../assets/Texture2D/boxExport0010.png", "../assets/Texture2D/boxExport0011.png",
        },
        false, 50, false, 100);
    m_Transform.scale = {0.75f, 0.75f};
    m_Transform.translation = {75 ,25};
    SetDrawable(m_Animation);
    SetZIndex(5);
}

void Box::Update() {
    // 更新動畫
    if (m_Animation) {
        m_Animation->Play();
    }
}

