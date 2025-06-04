//
// Created by LAB 1222 on 2025/5/23.
//

#include "Trap.h"


Trap::Trap() {
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

void Trap::Update() {

}