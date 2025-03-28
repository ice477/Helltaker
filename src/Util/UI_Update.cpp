//
// Created by Chucolate on 2025/3/28.
//
#include "UI_Subject.hpp"
#include "Char_Player.hpp"

void UI::Update(){
    if(Util::Input::IsKeyDown(KEY_LEFT)){
        PL.Move(-1,0);
    }
    if(Util::Input::IsKeyDown(VK_RIGHT)){
        PL.Move(1,0);
    }
    if(Util::Input::IsKeyDown(VK_UP)){
        PL.Move(0,1);
    }
    if(Util::Input::IsKeyDown(VK_DOWN)){
        PL.Move(0,-1);
    }
    if(Util::Input::IsKeyDown('Z')){
        //關卡的特殊動作
    }


    ////  |\/|
    ////Z(OWO)Z?
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (m_EnterDown) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
            ValidTask();
        }
    }
    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

    m_Root.Update();
}