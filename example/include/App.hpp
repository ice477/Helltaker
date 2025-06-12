#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"

#include "Cat.hpp"
#include "Giraffe.hpp"
#include "GiraffeText.hpp"
#include "dialogue_item/Trans.h"
#include "dialogue_item/Character.h"
#include "dialogue_item/DialogueBG.h"
#include "game_item/Box.h"
#include "game_item/Hero.h"
#include "game_item/StageBG.h"
#include "game_item/Gate.h"
#include "game_item/Enemy.h"
#include "game_item/Key.h"
#include "game_item/Trap.h"
#include "game_item/Target.h"
#include "game_item/Decoration.hpp"
#include "dialogue_item/DialogueBG.h"
#include "game_item/Decoration.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        PUSH_BOX,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }
    State m_NextState = State::START;
    bool m_IsTransitioning = false;

    void Start();
    void Update();
    void Push_Box();
    void End();

    void Visible();
    void CleaObjects();
    void SetOffset(int currentLevel);

    int m_OffsetX = -300;
    int m_OffsetY = -275;

    std::vector<std::vector<int>> m_MapData;

private:
    State m_CurrentState = State::START;

    std::shared_ptr<Giraffe> m_Giraffe = std::make_shared<Giraffe>();
    std::vector<std::shared_ptr<GiraffeText>> m_Giraffes;

    std::shared_ptr<Cat> m_Cat = std::make_shared<Cat>();

    std::shared_ptr<Trans> m_Trans = std::make_shared<Trans>();

    std::shared_ptr<Character> m_Character = std::make_shared<Character>();
    std::shared_ptr<DialogueBG> m_DialogueBG = std::make_shared<DialogueBG>();

    std::shared_ptr<StageBG> m_StageBG = std::make_shared<StageBG>();
    std::shared_ptr<Decoration> m_Decoration = std::make_shared<Decoration>();
    std::shared_ptr<DecorationRight> m_DecorationRight = std::make_shared<DecorationRight>();
    std::shared_ptr<DecorateLeft> m_DecorateLeft = std::make_shared<DecorateLeft>();
    std::shared_ptr<DecorateRight> m_DecorateRight = std::make_shared<DecorateRight>();

    std::shared_ptr<Decoration> m_Decorate = std::make_shared<Decoration>();

    std::shared_ptr<Hero> m_Hero = std::make_shared<Hero>();
    int m_StepLimit = 0;         // 當前關卡步數上限
    int m_StepsLeft = 0;         // 剩餘步數
    std::shared_ptr<GiraffeText> m_StepText;      // 步數顯示
    std::shared_ptr<GiraffeText> m_LevelText;     // 關卡顯示

    static constexpr int stepLimits[] = { 10, 1, 1, 1, 45, 50, 55, 60, 65 }; // 依關卡調整

    std::vector<std::shared_ptr<Box>> m_Boxes;
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    std::vector<std::shared_ptr<Gate>> m_Gates;
    std::vector<std::shared_ptr<Key>> m_Keys;
    std::vector<std::shared_ptr<Target>> m_Targets;
    std::vector<std::shared_ptr<Trap>> m_Traps;


    Util::Renderer m_Root;

    bool showDemoWindow = true;

    int isReload = false;

    int currentLevel = 1;

    MapManager m_MapManager;
};

#endif