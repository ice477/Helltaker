//
// Created by 蘇柏瑄 on 2025/6/13.
//

#include "Button.h"


Button::Button()
    : m_Animation(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/booper0001.png", "../assets/Texture2D/booper0002.png", "../assets/Texture2D/booper0003.png", "../assets/Texture2D/booper0004.png",
            "../assets/Texture2D/booper0005.png", "../assets/Texture2D/booper0006.png", "../assets/Texture2D/booper0007.png", "../assets/Texture2D/booper0008.png",
            "../assets/Texture2D/booper0009.png", "../assets/Texture2D/booper0010.png", "../assets/Texture2D/booper0011.png", "../assets/Texture2D/booper0012.png",
            "../assets/Texture2D/booper0013.png", "../assets/Texture2D/booper0014.png", "../assets/Texture2D/booper0015.png", "../assets/Texture2D/booper0016.png",
            "../assets/Texture2D/booper0017.png", "../assets/Texture2D/booper0018.png", "../assets/Texture2D/booper0019.png", "../assets/Texture2D/booper0020.png",
            "../assets/Texture2D/booper0021.png", "../assets/Texture2D/booper0022.png", "../assets/Texture2D/booper0023.png", "../assets/Texture2D/booper0024.png",
            "../assets/Texture2D/booper0025.png", "../assets/Texture2D/booper0026.png", "../assets/Texture2D/booper0027.png", "../assets/Texture2D/booper0028.png",
          },
          true, 50, true, 100)) {

    m_Transform.translation={0,-200};
    m_Transform.scale ={2.0f, 2.0f};
    m_Animation->SetFrameRange(0, 11); // 設置動畫範圍
    SetDrawable(m_Animation);
    SetZIndex(8);
}

void Button::Update() {
    m_Animation->Play();
}
