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


    m_Root.AddChild(m_Trans);
    m_Root.AddChild(m_Trans);

    m_Root.AddChild(m_StageBG);
    m_Root.AddChild(m_Hero);
    m_Root.AddChild(m_Box);
    m_Root.AddChild(m_Gate);
    m_Root.AddChild(m_Enemy);
    m_Root.AddChild(m_Key);



    m_CurrentState = State::UPDATE;
}

void App::Update() {
    if (m_CurrentState == State::PUSH_BOX) {
        // 初始化地圖和物件
        MapManager mapManager;
        if (mapManager.LoadMap("../assets/maps/test_map.txt")) {
            LOG_INFO("Map loaded successfully for level {}", currentLevel);

            const auto& mapData = mapManager.GetMapData();
            constexpr int tileSize = 75;
            constexpr int offsetX = -225;
            constexpr int offsetY = -275;

            for (int y = 0; y < static_cast<int>(mapData.size()); y++) {
                for (int x = 0; x < static_cast<int>(mapData[y].size()); x++) {
                    int tile = mapData[y][x];
                    int worldX = offsetX + x * tileSize;
                    int worldY = offsetY + y * tileSize;

                    switch (tile) {
                    case 2: // Hero
                        m_Hero->m_Transform.translation = {worldX, worldY};
                        m_Hero->SetVisible(true);
                        LOG_DEBUG("Hero placed at ({}, {})", worldX, worldY);
                        break;
                    case 3: // Box
                        m_Box->m_Transform.translation = {worldX, worldY};
                        m_Box->SetVisible(true);
                        LOG_DEBUG("Box placed at ({}, {})", worldX, worldY);
                        break;
                    case 4: // Enemy
                        m_Enemy->m_Transform.translation = {worldX, worldY};
                        m_Enemy->SetVisible(true);
                        LOG_DEBUG("Enemy placed at ({}, {})", worldX, worldY);
                        break;
                    case 5: // Gate
                        m_Gate->m_Transform.translation = {worldX, worldY};
                        m_Gate->SetVisible(true);
                        LOG_DEBUG("Gate placed at ({}, {})", worldX, worldY);
                        break;
                    case 6: // Key
                        m_Key->m_Transform.translation = {worldX, worldY};
                        m_Key->SetVisible(true);
                        LOG_DEBUG("Key placed at ({}, {})", worldX, worldY);
                        break;
                    default:
                        break;
                    }
                }
            }
        } else {
            LOG_ERROR("Failed to load map for level {}", currentLevel);
        }
    }

    Visible();
    m_Character->Update();
    m_Character->SetVisible(true);

    m_Trans->Update();
    m_Cat->Update();
    m_Root.Update();

    if (Util::Input::IsKeyDown(Util::Keycode::K)) {
        LOG_DEBUG("K Pressed. Switching to PUSH_BOX scene.");
        m_CurrentState = State::PUSH_BOX;
    }
}

void App::Push_Box() {
    Visible();

    m_StageBG->Update();
    m_Trans->Update();

    m_Hero->Update();
    m_Box->Update();
    m_Gate->Update();
    m_Enemy->Update();
    m_Key->Update();
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
        m_Box->SetVisible(false);
        m_Gate->SetVisible(false);
        m_Enemy->SetVisible(false);
        m_Key->SetVisible(false);
    } else if (m_CurrentState == State::PUSH_BOX) {
        m_Character->SetVisible(false);
        m_StageBG->SetVisible(true);
        m_Hero->SetVisible(true);
        m_Box->SetVisible(true);
        m_Gate->SetVisible(true);
        m_Enemy->SetVisible(true);
        m_Key->SetVisible(true);
    } else {
        m_Character->SetVisible(false);
        m_StageBG->SetVisible(false);
    }
}