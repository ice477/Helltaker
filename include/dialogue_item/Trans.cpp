#include "Trans.h"
#include "../example/include/App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
Trans::Trans()
: m_Animation(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/transition0002.png", "../assets/Texture2D/transition0003.png", "../assets/Texture2D/transition0004.png", "../assets/Texture2D/transition0005.png",
              "../assets/Texture2D/transition0006.png", "../assets/Texture2D/transition0007.png", "../assets/Texture2D/transition0008.png", "../assets/Texture2D/transition0009.png",
              "../assets/Texture2D/transition0010.png", "../assets/Texture2D/transition0011.png", "../assets/Texture2D/transition0012.png", "../assets/Texture2D/transition0013.png",
              "../assets/Texture2D/transition0014.png", "../assets/Texture2D/transition0015.png", "../assets/Texture2D/transition0016.png", "../assets/Texture2D/transition0017.png",
            "../assets/Texture2D/transition0018.png", "../assets/Texture2D/transition0019.png", "../assets/Texture2D/transition0020.png", "../assets/Texture2D/transition0021.png",
            "../assets/Texture2D/transition0022.png", "../assets/Texture2D/transition0023.png", "../assets/Texture2D/transition0024.png", "../assets/Texture2D/transition0025.png",
            "../assets/Texture2D/transition0026.png", "../assets/Texture2D/transition0027.png", "../assets/Texture2D/transition0028.png", "../assets/Texture2D/transition0029.png",
            "../assets/Texture2D/transition0030.png"
         },
          true, 50, false, 100)) {
     m_Transform.scale = {0.65f, 0.65f};
     SetDrawable(m_Animation);
     SetZIndex(10);
     SetVisible(false);
    m_Animation->SetCurrentFrame(28);
     m_Animation->SetFrameRange(0, 28); // 設置動畫範圍
}


void Trans::Update(State appState, bool textEnd) {
     if (m_Animation->GetCurrentFrameIndex() == 0) {
         m_Animation->Play();
         SetVisible(true);
     }
     else if (m_Animation->GetCurrentFrameIndex() == 28) {
         m_Animation->Pause();
         SetVisible(false);
     }

    if (m_Hero && m_Hero->HeroDead()) {
        m_Animation->SetCurrentFrame(0);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::K)) {
        m_Animation->SetCurrentFrame(0);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::SPACE) && appState == State::UPDATE && textEnd == true) {
        m_Animation->SetCurrentFrame(0);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::R)) {
        m_Animation->SetCurrentFrame(0);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::B)&& appState == State::UPDATE) {
        m_Animation->SetCurrentFrame(0);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::N)&& appState == State::UPDATE) {
        m_Animation->SetCurrentFrame(0);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::M)&& appState == State::UPDATE) {
        m_Animation->SetCurrentFrame(0);
    }
 }