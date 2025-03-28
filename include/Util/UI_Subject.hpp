//
// Created by Iced on 2025/3/14.
//--->UI整合

#ifndef UI_SUBJECT_HPP
#define UI_SUBJECT_HPP

//include "image.hpp"//圖片
//#include "Animation.hpp"//動畫
//#include "KeyInput.hpp"//輸入
#include "LoadTextFile.hpp"//
//#include "Outtext.hpp"//
#include "Interact.hpp"//
//#include ""//
class Subject{
public:
    enum class State{
        START,
        UPDATE,
        END,
    };
    State GetCurrentState()const{return m_CurrentState; }

    void Start();

    void Update();

    void End();

private:
    void VaildTask();
private://特殊關卡調整用
    enum class Mode{
        Normal,
    };

    State m_CurrentState = State::START;
    Mode m_Mode = Mode::Normal;

};
#endif //UI_SUBJECT_HPP
