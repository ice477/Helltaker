#include "Key.h"

Key::Key() {
    m_Animation = std::make_shared<Util::Animation>(
        std::vector<std::string>{
            "../assets/Texture2D/assets100V20104.png", "../assets/Texture2D/assets100V20105.png", "../assets/Texture2D/assets100V20106.png", "../assets/Texture2D/assets100V20107.png",
            "../assets/Texture2D/assets100V20108.png", "../assets/Texture2D/assets100V20109.png", "../assets/Texture2D/assets100V20110.png", "../assets/Texture2D/assets100V20111.png",
            "../assets/Texture2D/assets100V20112.png", "../assets/Texture2D/assets100V20113.png", "../assets/Texture2D/assets100V20114.png", "../assets/Texture2D/assets100V20115.png"
        },
        true, 50, true, 100);
    m_Transform.scale = {0.75f, 0.75f};
    SetDrawable(m_Animation);
    m_Animation->SetFrameRange(0, 11); // 設置動畫範圍
    SetZIndex(3); // 設置渲染層級
}

void Key::Update() {
    // 更新動畫
    if (m_Animation) {
        m_Animation->Play();
    }
}