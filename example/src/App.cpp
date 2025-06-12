#include "App.hpp"
#include "GiraffeText.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Renderer.hpp"
#include "game_item/StageBG.h"
#include "game_item/MapManager.h"
#include "game_item/Decoration.hpp"

void App::Start() {
    LOG_TRACE("Start");

    m_Root.AddChild(m_Character);
    m_Character->SetVisible(false);


    m_Root.AddChild(m_Trans);
    m_Root.AddChild(m_Trans);

    m_Root.AddChild(m_StageBG);
    m_StageBG->SetVisible(false);

    m_Root.AddChild(m_DialogueBG);

    m_Root.AddChild(m_Decoration);
    m_Root.AddChild(m_DecorationRight);
    m_Root.AddChild(m_DecorateLeft);
    m_Root.AddChild(m_DecorateRight);

    m_StepText = std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 80);
    m_LevelText = std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf" ,80);
    m_StepText->Start();
    m_LevelText->Start();
    m_StepText->SetZIndex(8);
    m_LevelText->SetZIndex(8);
    m_Root.AddChild(m_StepText);
    m_Root.AddChild(m_LevelText);

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
    for (const auto &target: m_Targets) {
        m_Root.AddChild(target);
    }
    for (const auto& trap:m_Traps) {
        m_Root.AddChild(trap);
    }

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    Visible();

    m_Character->Update();
    m_DialogueBG->Update();
    m_Trans->Update();
    m_Cat->Update();
    m_Root.Update();

    //dialogueBG.Update(); // 確保背景的 Update 被調用
    //character.Update();  // 確保角色的 Update 被調用
    if (Util::Input::IsKeyDown(Util::Keycode::K)) {
        LOG_DEBUG("K Pressed. Switching to PUSH_BOX scene.");
        m_CurrentState = State::PUSH_BOX;
    }
}

void App::Push_Box() {
    static bool isMapLoaded = false; // 靜態變量，用於記錄地圖是否已加載

    if (!isMapLoaded) {
        CleaObjects();
        LOG_DEBUG("Initializing map for PUSH_BOX scene.");

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
            m_MapData.clear();
            m_MapData = mapManager.GetMapDataMutable();
            constexpr int tilesize = 75;

            // 統計各類 tile 數量
            int boxCount = 0, enemyCount = 0, gateCount = 0, keyCount = 0,targetCount =0, trapCount = 0;
            for (const auto& row : m_MapData) {
                for (int tile : row) {
                    if (tile == 3) boxCount++;
                    if (tile == 4) enemyCount++;
                    if (tile == 5) gateCount++;
                    if (tile == 6) keyCount++;
                    if (tile == 7) targetCount++;
                    if (tile == 8) trapCount++;
                }
            }
            m_Boxes.resize(0); m_Enemies.resize(0); m_Gates.resize(0); m_Keys.resize(0); m_Traps.resize(0);
            m_Boxes.reserve(boxCount);
            m_Enemies.reserve(enemyCount);
            m_Gates.reserve(gateCount);
            m_Keys.reserve(keyCount);
            m_Targets.reserve(targetCount);
            m_Traps.reserve(trapCount);

            int boxIndex = 0, enemyIndex = 0, gateIndex = 0, keyIndex = 0,targetIndex = 0, trapIndex = 0;
            for (int y = 0; y < static_cast<int>(m_MapData.size()); y++) {
                for (int x = 0; x < static_cast<int>(m_MapData[y].size()); x++) {
                    int tile = m_MapData[y][x];
                    int worldX = m_OffsetX + x * tilesize;
                    int worldY = m_OffsetY + (static_cast<int>(m_MapData.size()) - 1 - y) * tilesize;
                    switch (tile) {
                    case 2:
                        if (!m_Hero) {
                            m_Hero = std::make_shared<Hero>();
                            m_Hero->SetMapData(m_MapData, worldX, worldY);
                            m_Hero->SetOffset(m_OffsetX, m_OffsetY);
                        }
                        m_Hero->m_Transform.translation = {worldX, worldY};
                        m_Hero->SetVisible(true);
                        break;
                    case 3://box
                        m_Boxes.push_back(std::make_shared<Box>(boxIndex++));
                        m_Boxes.back()->SetOffset(m_OffsetX, m_OffsetY);
                        m_Boxes.back()->m_Transform.translation = {worldX, worldY};
                        break;
                    case 4://enemy
                        m_Enemies.push_back(std::make_shared<Enemy>(enemyIndex++));
                        m_Enemies.back()->SetOffset(m_OffsetX, m_OffsetY);
                        m_Enemies.back()->m_Transform.translation = {worldX, worldY};
                        break;
                    case 5://gate
                        m_Gates.push_back(std::make_shared<Gate>(gateIndex++));
                        m_Gates.back()->SetOffset(m_OffsetX, m_OffsetY);
                        m_Gates.back()->m_Transform.translation = {worldX, worldY};
                        break;
                    case 6: // key
                        m_Keys.push_back(std::make_shared<Key>(keyIndex++));
                        m_Keys.back()->SetOffset(m_OffsetX, m_OffsetY);
                        m_Keys.back()->m_Transform.translation = {worldX, worldY};
                        break;
                    case 7: //target
                        m_Targets.push_back(std::make_shared<Target>(targetIndex++,currentLevel));
                        m_Targets.back()->SetOffset(m_OffsetX, m_OffsetY);
                        m_Targets.back()->m_Transform.translation = {worldX, worldY + 25};
                        break;
                    case 8:
                        m_Traps.push_back(std::make_shared<Trap>(trapIndex++));
                        m_Traps.back()->SetOffset(m_OffsetX, m_OffsetY);
                        break;
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
            for (const auto& target : m_Targets) m_Root.AddChild(target);
            for (const auto& trap : m_Traps) m_Root.AddChild(trap);

            isMapLoaded = true; // 設置地圖加載狀態為已加載
        } else {
            LOG_ERROR("Failed to load map for level {}", currentLevel);
        }

        // 更新關卡顯示（羅馬數字）
        static const char* roman[] = {
            "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
            "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
            "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX"
        };
        if (m_LevelText) {
            m_LevelText->m_Transform.translation = { 530, -200 };
            m_LevelText->m_Text->SetText(fmt::format("{}", roman[currentLevel]));
        }
        m_StepLimit = stepLimits[currentLevel - 1];
        m_StepsLeft = m_StepLimit;
        m_Hero->SetSteps(m_StepLimit);
    }

    m_StageBG->Update(currentLevel);
    m_Trans->Update();

    if (m_Hero) {
        m_Hero->Update(m_MapData);
        m_StepsLeft = m_Hero->GetSteps();
        m_StepText->m_Transform.translation = { -520, -200 };
        if (m_StepText && m_StepText->m_Text&&m_StepsLeft > 0) {
            m_StepText->m_Text->SetText(fmt::format("{}", m_StepsLeft));
        }
        else if (m_StepText && m_StepText->m_Text&&m_StepsLeft == 0) {
            m_StepText->m_Text->SetText(fmt::format("X"));
        }
    }
    for (const auto& box : m_Boxes) box->Update(m_MapData);
    for (const auto& enemy : m_Enemies) enemy->Update(m_MapData);
    for (const auto& gate : m_Gates) gate->Update(m_MapData);
    for (const auto& key : m_Keys) key->Update(m_MapData);
    for (const auto& trap : m_Traps) trap->Update(m_MapData);
    m_Root.Update();

    Visible();

    if (m_Hero && m_Hero->PassedLevel()) {
        LOG_DEBUG("Level passed! Switching to next level.");
        m_Trans->m_Animation->SetCurrentFrame(0);
        m_CurrentState = State::UPDATE;
        currentLevel++;
        SetOffset(currentLevel);
        isMapLoaded = false;
        m_Hero->m_PassedLevel = false;
    }

    if (m_Hero->HeroDead()) {
        if (m_Hero->m_Animation->GetCurrentFrameIndex() == 66) {
            m_Trans->m_Animation->SetCurrentFrame(0);
            SetOffset(currentLevel);
            isMapLoaded = false;
            m_Hero->m_HeroDead = false; // 重置英雄死亡狀態
        }
    }

    if (Util::Input::IsKeyDown(Util::Keycode::K)) {
        LOG_DEBUG("K Pressed. Switching to UPDATE scene.");
        m_CurrentState = State::UPDATE;
        currentLevel++;
        SetOffset(currentLevel);
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
    // 1. Hero 死亡時優先處理，只顯示 Hero
    if (m_Hero && m_Hero->HeroDead()) {
        m_StageBG->SetVisible(false);
        m_Hero->SetVisible(true);
        for (const auto& box : m_Boxes) box->SetVisible(false);
        for (const auto& gate : m_Gates) gate->SetVisible(false);
        for (const auto& enemy : m_Enemies) enemy->SetVisible(false);
        for (const auto& key : m_Keys) key->SetVisible(false);
        for (const auto& target : m_Targets) target->SetVisible(false);
        for (const auto& trap : m_Traps) trap->SetVisible(false);
        return;
    }

    // 2. 其他狀態依照 m_CurrentState 控制
    if (m_CurrentState == State::UPDATE) {
        m_StageBG->SetVisible(false);
        if (m_Hero) m_Hero->SetVisible(false);
        m_StepText->SetVisible(false);
        m_LevelText->SetVisible(false);
        for (const auto& box : m_Boxes) box->SetVisible(false);
        for (const auto& gate : m_Gates) gate->SetVisible(false);
        for (const auto& enemy : m_Enemies) enemy->SetVisible(false);
        for (const auto& key : m_Keys) key->SetVisible(false);
        for (const auto& target : m_Targets) target->SetVisible(false);
        for (const auto& trap : m_Traps) trap->SetVisible(false);
        m_DialogueBG->SetVisible(true);
        m_Decoration->SetVisible(false);
        m_DecorationRight->SetVisible(false);
        m_DecorateLeft->SetVisible(false);
        m_DecorateRight->SetVisible(false);
    }
    else if (m_CurrentState == State::PUSH_BOX) {
        m_Character->SetVisible(false);
        m_StageBG->SetVisible(true);
        m_DialogueBG->SetVisible(false);
        m_Decoration->SetVisible(true);
        m_DecorationRight->SetVisible(true);
        m_DecorateLeft->SetVisible(true);
        m_DecorateRight->SetVisible(true);

        if (m_Hero) m_Hero->SetVisible(true);
        m_StepText->SetVisible(true);
        m_LevelText->SetVisible(true);
        for (const auto& box : m_Boxes) box->SetVisible(true);
        for (const auto& gate : m_Gates) gate->SetVisible(true);
        for (const auto& enemy : m_Enemies) enemy->SetVisible(true);
        for (const auto& key : m_Keys) key->SetVisible(true);
        for (const auto& target : m_Targets) target->SetVisible(true);
        for (const auto& trap : m_Traps) trap->SetVisible(true);
        m_DecorationRight->Update();
        m_Decoration->Update();
        m_DecorateLeft->Update();
        m_DecorateRight->Update();
    }
    else {
        m_Character->SetVisible(false);
        m_StageBG->SetVisible(false);
    }
}


void App::CleaObjects() {
    if (m_Hero)
    {
        m_Root.RemoveChild(m_Hero);
        }
    for (const auto& box : m_Boxes) m_Root.RemoveChild(box);
    for (const auto& enemy : m_Enemies) m_Root.RemoveChild(enemy);
    for (const auto& gate : m_Gates) m_Root.RemoveChild(gate);
    for (const auto& key : m_Keys) m_Root.RemoveChild(key);
    for (const auto& target : m_Targets) m_Root.RemoveChild(target);
    for (const auto& trap : m_Traps) m_Root.RemoveChild(trap);
    m_Hero.reset();
    m_Boxes.clear();
    m_Enemies.clear();
    m_Gates.clear();
    m_Keys.clear();
    m_Targets.clear();
    m_Traps.clear();
}


void App::SetOffset(int currentLevel) {
    if (currentLevel == 1 || currentLevel == 2) {
        m_OffsetX = -300;
        m_OffsetY = -275;
    } else if (currentLevel == 3) {
        m_OffsetX = -335;
        m_OffsetY = -310;
    }else if (currentLevel == 4) {
        m_OffsetX = -335;
        m_OffsetY = -235;
    } else if (currentLevel == 5) {
        m_OffsetX = -260;
        m_OffsetY = -310;
    } else if (currentLevel == 6) {
        m_OffsetX = -300;
        m_OffsetY = -350;
    } else if (currentLevel == 7) {
        m_OffsetX = -260;
        m_OffsetY = -315;
    } else if (currentLevel == 8) {
        m_OffsetX = -375;
        m_OffsetY = -340;

    }
    // Hero
    if (m_Hero) m_Hero->SetOffset(m_OffsetX, m_OffsetY);
    for (auto& box : m_Boxes) box->SetOffset(m_OffsetX, m_OffsetY);
    for (auto& enemy : m_Enemies) enemy->SetOffset(m_OffsetX, m_OffsetY);
    for (auto& key : m_Keys) key->SetOffset(m_OffsetX, m_OffsetY);
    for (auto& target : m_Targets) target->SetOffset(m_OffsetX, m_OffsetY);
    for (auto& trap : m_Traps) trap->SetOffset(m_OffsetX, m_OffsetY);
}