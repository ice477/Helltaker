#include "App.hpp"
#include "GiraffeText.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Renderer.hpp"
#include "game_item/StageBG.h"
#include "game_item/MapManager.h"
#include "game_item/Decorate.hpp"

void App::Start() {
    LOG_TRACE("Start");

    m_Root.AddChild(m_Character);
    m_Character->SetVisible(false);

    m_Root.AddChild(m_Trans);
    m_Root.AddChild(m_Trans);

    m_Root.AddChild(m_StageBG);
    m_StageBG->SetVisible(false);

    m_Root.AddChild(m_DialogueBG);

    m_Root.AddChild(m_Hero);
    m_Hero->SetVisible(false);

    m_Root.AddChild(m_Decorate);
    for (const auto& gate : m_Gates) {
        m_Root.AddChild(gate);
    }
    for (const auto& key : m_Keys) {
        m_Root.AddChild(key);
    }
    for (const auto& enemy : m_Enemies) {
        m_Root.AddChild(enemy);
    }
    for (const auto& box : m_Boxes) {
        m_Root.AddChild(box);
    }

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    Visible();
    //m_Hero -> SetVisible(false);

    m_DialogueBG->SetVisible(true);
    m_DialogueBG->Update();
    m_Character->Update();
    //m_Character->SetVisible(true);

    m_Trans->Update();
    m_Cat->Update();
    m_Root.Update();

    if (Util::Input::IsKeyDown(Util::Keycode::K)) {
        LOG_DEBUG("K Pressed. Switching to PUSH_BOX scene.");
        m_CurrentState = State::PUSH_BOX;
    }
}

void App::Push_Box() {
    m_DialogueBG->SetVisible(false);
    static bool isMapLoaded = false; // 靜態變量，用於記錄地圖是否已加載

    if (!isMapLoaded) {
        LOG_DEBUG("Initializing map for PUSH_BOX scene.");

        // 清除當前關卡的物件
        m_Hero.reset();
        m_Boxes.clear();
        m_Enemies.clear();
        m_Gates.clear();
        m_Keys.clear();

        // 初始化地圖和物件
        MapManager mapManager;
        if (mapManager.LoadMap("../assets/maps/test_map.txt")) {
            LOG_INFO("Map loaded successfully for level {}", currentLevel);

            auto& mapData = mapManager.GetMapDataMutable();
            constexpr int tilesize = 75;
            constexpr int offsetX = -300;
            constexpr int offsetY = -275;

            for (int y = 0; y < static_cast<int>(mapData.size()); y++) {
                for (int x = 0; x < static_cast<int>(mapData[y].size()); x++) {
                    int tile = mapData[y][x];
                    int worldX = offsetX + x * tilesize; // X 軸保持不變
                    int worldY = offsetY + (mapData.size() - 1 - y) * tilesize; // Y 軸翻轉
                    fmt::print("worldX: {}, worldY: {}, mapdata_size: {}\n", worldX, worldY, mapData.size());

                    switch (tile) {
                    case 2: { // Hero
                        if (!m_Hero) {
                            m_Hero = std::make_shared<Hero>();
                            m_Hero->SetMapData(mapData);
                        }
                        m_Hero->m_Transform.translation = {worldX, worldY};
                        m_Hero->SetVisible(true);
                        LOG_DEBUG("Hero placed at ({}, {})", worldX, worldY);
                        break;
                    }
                    case 3: { // Box
                        auto box = std::make_shared<Box>();
                        box->m_Transform.translation = {worldX, worldY};
                        box->SetVisible(true);
                        m_Boxes.push_back(box);
                        LOG_DEBUG("Box placed at ({}, {})", worldX, worldY);
                        break;
                    }
                    case 4: { // Enemy
                        auto enemy = std::make_shared<Enemy>();
                        enemy->m_Transform.translation = {worldX, worldY};
                        enemy->SetVisible(true);
                        m_Enemies.push_back(enemy);
                        LOG_DEBUG("Enemy placed at ({}, {})", worldX, worldY);
                        break;
                    }
                    case 5: { // Gate
                        auto gate = std::make_shared<Gate>();
                        gate->m_Transform.translation = {worldX, worldY};
                        gate->SetVisible(true);
                        m_Gates.push_back(gate);
                        LOG_DEBUG("Gate placed at ({}, {})", worldX, worldY);
                        break;
                    }
                    case 6: { // Key
                        auto key = std::make_shared<Key>();
                        key->m_Transform.translation = {worldX, worldY};
                        key->SetVisible(true);
                        m_Keys.push_back(key);
                        LOG_DEBUG("Key placed at ({}, {})", worldX, worldY);
                        break;
                    }
                    case 7: { // Target
                        auto key = std::make_shared<Key>();
                        key->m_Transform.translation = {worldX, worldY};
                        key->SetVisible(true);
                        m_Keys.push_back(key);
                        LOG_DEBUG("Key placed at ({}, {})", worldX, worldY);
                        break;
                    }
                    default:
                        break;
                    }
                }
            }

            // 將所有物件添加到場景樹中
            m_Root.AddChild(m_Hero);
            for (const auto& box : m_Boxes) m_Root.AddChild(box);
            for (const auto& enemy : m_Enemies) m_Root.AddChild(enemy);
            for (const auto& gate : m_Gates) m_Root.AddChild(gate);
            for (const auto& key : m_Keys) m_Root.AddChild(key);

            isMapLoaded = true; // 標記地圖已加載
        } else {
            LOG_ERROR("Failed to load map for level {}", currentLevel);
        }
    }

    Visible();

    m_StageBG->Update(currentLevel);
    m_Trans->Update();


    m_Hero->Update();
    for (const auto& box : m_Boxes) box->Update();
    for (const auto& enemy : m_Enemies) enemy->Update();
    for (const auto& gate : m_Gates) gate->Update();
    for (const auto& key : m_Keys) key->Update();
    m_Root.Update();

    if (Util::Input::IsKeyDown(Util::Keycode::K)) {
        LOG_DEBUG("K Pressed. Switching to UPDATE scene.");
        m_CurrentState = State::UPDATE;
        currentLevel++;
        isMapLoaded = false; // 重置地圖加載狀態
    }
}

void App::End() {
    LOG_TRACE("End");
}

void App::Visible() {
    if (m_CurrentState == State::UPDATE) {
        //m_Character->SetVisible(false);
        m_StageBG->SetVisible(false);

        m_Hero->SetVisible(false);
        for (const auto& box : m_Boxes) box->SetVisible(false);
        for (const auto& gate : m_Gates) gate->SetVisible(false);
        for (const auto& enemy : m_Enemies) enemy->SetVisible(false);
        for (const auto& key : m_Keys) key->SetVisible(false);
    } else if (m_CurrentState == State::PUSH_BOX) {
        m_Character->SetVisible(false);
        m_StageBG->SetVisible(true);

        m_Hero->SetVisible(true);
        for (const auto& box : m_Boxes) box->SetVisible(true);
        for (const auto& gate : m_Gates) gate->SetVisible(true);
        for (const auto& enemy : m_Enemies) enemy->SetVisible(true);
        for (const auto& key : m_Keys) key->SetVisible(true);
    } else {
        m_Character->SetVisible(false);
        m_StageBG->SetVisible(false);
    }
}