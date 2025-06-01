#include "App.hpp"
#include "GiraffeText.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Renderer.hpp"
#include "game_item/StageBG.h"
#include "game_item/MapManager.h"

void App::Start() {
    LOG_TRACE("Start");

    m_Root.AddChild(m_Character);


    m_Root.AddChild(m_Trans);
    m_Root.AddChild(m_Trans);

    m_Root.AddChild(m_StageBG);

    m_Root.AddChild(m_Hero);
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
    for (const auto& trap:m_Traps) {
        m_Root.AddChild(trap);
    }

    m_CurrentState = State::UPDATE;
}

void App::Update() {

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
    static bool isMapLoaded = false; // 靜態變量，用於記錄地圖是否已加載

    if (!isMapLoaded) {
        LOG_DEBUG("Initializing map for PUSH_BOX scene.");
        CleaObjects();
        // 清除當前關卡的物件
        m_Hero.reset();
        m_Boxes.clear();
        m_Enemies.clear();
        m_Gates.clear();
        m_Keys.clear();
        m_Traps.clear();

        // 初始化地圖和物件
        MapManager mapManager;
        if (mapManager.LoadMap(currentLevel)) {
            LOG_INFO("Map loaded successfully for level {}", currentLevel);


            m_MapData = mapManager.GetMapDataMutable();
            constexpr int tilesize = 75;
            constexpr int offsetX = -300;
            constexpr int offsetY = -275;

            int boxIndex = 0;
            int enemyIndex = 0;
            int gateIndex = 0;

            for (int y = 0; y < static_cast<int>(m_MapData.size()); y++) {
                for (int x = 0; x < static_cast<int>(m_MapData[y].size()); x++) {
                    int tile = m_MapData[y][x];
                    int worldX = offsetX + x * tilesize; // X 軸保持不變
                    int worldY = offsetY + (m_MapData.size() - 1 - y) * tilesize; // Y 軸翻轉
                    fmt::print("worldX: {}, worldY: {}, mapdata_size: {}\n", worldX, worldY, m_MapData.size());

                    switch (tile) {
                    case 2: { // Hero
                        if (!m_Hero) {
                            m_Hero = std::make_shared<Hero>();
                            m_Hero->SetMapData(m_MapData);
                        }
                        m_Hero->m_Transform.translation = {worldX, worldY};
                        m_Hero->SetVisible(true);
                        LOG_DEBUG("Hero placed at ({}, {})", worldX, worldY);
                        break;
                    }
                    case 3: { // Box
                        auto box = std::make_shared<Box>(boxIndex++);
                        box->m_Transform.translation = {worldX, worldY};
                        box->SetVisible(true);
                        m_Boxes.push_back(box);
                        break;
                    }
                    case 4: { // Enemy
                        auto enemy = std::make_shared<Enemy>(enemyIndex++);
                        enemy->m_Transform.translation = {worldX, worldY};
                        enemy->SetVisible(true);
                        m_Enemies.push_back(enemy);
                        break;
                    }
                    case 5: { // Gate
                        auto gate = std::make_shared<Gate>(gateIndex++);
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
                    case 8:{ //trap
                        auto trap = std::make_shared<Trap>();
                        trap->m_Transform.translation = {worldX, worldY};
                        trap->SetVisible(true);
                        m_Traps.push_back(trap);
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
            for (const auto& trap : m_Traps) m_Root.AddChild(trap);

            isMapLoaded = true; // 設置地圖加載狀態為已加載
        } else {
            LOG_ERROR("Failed to load map for level {}", currentLevel);
        }
    }

    Visible();

    m_StageBG->Update(currentLevel);
    m_Trans->Update();


    m_Hero->Update(m_MapData);
    for (const auto& box : m_Boxes) box->Update(m_MapData);
    for (const auto& enemy : m_Enemies) enemy->Update(m_MapData);
    for (const auto& gate : m_Gates) gate->Update(m_MapData);
    for (const auto& key : m_Keys) key->Update(m_MapData);
    m_Root.Update();

    if (Util::Input::IsKeyDown(Util::Keycode::K)) {
        LOG_DEBUG("K Pressed. Switching to UPDATE scene.");
        m_CurrentState = State::UPDATE;
        currentLevel++;
        isMapLoaded = false; // 重置地圖加載狀態
    }

    if (Util::Input::IsKeyDown(Util::Keycode::R)) {
        LOG_DEBUG("R Pressed. Reloading current level.");
        isMapLoaded = false;
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

void App::CleaObjects() {
    m_Root.RemoveChild(m_Hero);
    for (const auto& box : m_Boxes) m_Root.RemoveChild(box);
    for (const auto& enemy : m_Enemies) m_Root.RemoveChild(enemy);
    for (const auto& gate : m_Gates) m_Root.RemoveChild(gate);
    for (const auto& key : m_Keys) m_Root.RemoveChild(key);
    for (const auto& trap : m_Traps) m_Root.RemoveChild(trap);
}