#include "Hero.h"
#include "Util/Input.hpp"



Hero::Hero()
    : m_Animation(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              // DEFAULT
              "../assets/Texture2D/hero0022.png", "../assets/Texture2D/hero0023.png", "../assets/Texture2D/hero0024.png", "../assets/Texture2D/hero0025.png",
              "../assets/Texture2D/hero0026.png", "../assets/Texture2D/hero0027.png","../assets/Texture2D/hero0028.png", "../assets/Texture2D/hero0029.png",
              "../assets/Texture2D/hero0030.png", "../assets/Texture2D/hero0031.png","../assets/Texture2D/hero0032.png", "../assets/Texture2D/hero0033.png",

              // MOVE
              "../assets/Texture2D/assets100V20053.png", "../assets/Texture2D/assets100V20054.png", "../assets/Texture2D/assets100V20055.png", "../assets/Texture2D/assets100V20056.png",
              "../assets/Texture2D/assets100V20057.png", "../assets/Texture2D/assets100V20058.png",

              // KICK
              "../assets/Texture2D/hero0040.png", "../assets/Texture2D/hero0041.png", "../assets/Texture2D/hero0042.png", "../assets/Texture2D/hero0043.png",
              "../assets/Texture2D/hero0044.png", "../assets/Texture2D/hero0045.png", "../assets/Texture2D/hero0046.png", "../assets/Texture2D/hero0047.png",
              "../assets/Texture2D/hero0048.png", "../assets/Texture2D/hero0049.png", "../assets/Texture2D/hero0050.png", "../assets/Texture2D/hero0051.png",
              "../assets/Texture2D/hero0052.png",
              // WIN
              "../assets/Texture2D/hero0050.png", "../assets/Texture2D/hero0051.png", "../assets/Texture2D/hero0052.png", "../assets/Texture2D/hero0059.png",
          },
          true, 50, true, 100)) {
    m_Transform.scale = {0.65f, 0.65f};
    m_Transform.translation = {0 ,110};
    SetDrawable(m_Animation);
    m_Animation->SetFrameRange(0,11);
    SetZIndex(5);
    m_State = State::DEFAULT;
}


void Hero::Update() {
    //移動邏輯
    if (m_State != State::MOVE) {
        if (Util::Input::IsKeyDown(Util::Keycode::S)) {
            m_Transform.translation.y -= 75;
        } else if (Util::Input::IsKeyDown(Util::Keycode::W)) {
            m_Transform.translation.y += 75;
        } else if (Util::Input::IsKeyDown(Util::Keycode::A)) {
            m_Transform.translation.x -= 75;
            m_Transform.scale.x = -0.65f;
        } else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
            m_Transform.translation.x += 75;
            m_Transform.scale.x = 0.65f;
        }
    }



}

