#include "App.hpp"
#include "GiraffeText.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Renderer.hpp"
#include "game_item/StageBG.h"

void App::Start() {
    LOG_TRACE("Start");

    m_Giraffe->SetDrawable(
        std::make_shared<Util::Image>("../assets/Texture2D/boxExport0001.png", "../assets/Texture2D/boxExport0002.png"));
    m_Giraffe->SetZIndex(4);
    m_Giraffe->Start();
    m_Giraffe->SetVisible(false);


    m_Root.AddChild(m_Cat);
    m_Cat->SetVisible(false);

    m_Root.AddChild(m_Character);

    m_Root.AddChild(m_StageBG);
    m_Root.AddChild(m_Hero);

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    Visible();

    m_Character->Update();
    m_Character->SetVisible(true);

    m_Giraffe->Update();
    m_Cat->Update();
    m_Root.Update();

    if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
        showDemoWindow = !showDemoWindow;
    }
    if (showDemoWindow) {
        ImGui::ShowDemoWindow();
    }

    if (Util::Input::IsKeyDown(Util::Keycode::K)) {
        LOG_DEBUG("K Pressed. Switching to PUSH_BOX scene.");
        m_CurrentState = State::PUSH_BOX;
    }
}

void App::Push_Box() {
    Visible();

    m_StageBG->Update();
    m_Hero->Update();
    m_Root.Update();
    if (Util::Input::IsKeyDown(Util::Keycode::K)) {
        LOG_DEBUG("K Pressed. Switching to PUSH_BOX scene.");
        m_CurrentState = State::UPDATE;
        currentLevel ++;
    }
}

void App::End() {
    LOG_TRACE("End");
}

void App::Visible() {
    if (m_CurrentState == State::UPDATE) {
        m_Character->SetVisible(true);
        m_StageBG->SetVisible(false);
        m_Hero->SetVisible(false);
    } else if (m_CurrentState == State::PUSH_BOX) {
        m_Character->SetVisible(false);
        m_StageBG->SetVisible(true);
        m_Hero->SetVisible(true);
    } else {
        m_Character->SetVisible(false);
        m_StageBG->SetVisible(false);
    }
}