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
#include "game_item/Decoration.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        PUSH_BOX,
        TRANS,
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


    std::vector<std::shared_ptr<Hero>> m_Heroes;
    std::vector<std::shared_ptr<Box>> m_Boxes;
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    std::vector<std::shared_ptr<Gate>> m_Gates;
    std::vector<std::shared_ptr<Key>> m_Keys;
    //std::vector<std::shared_ptr<Decoration>> m_Decoration;

    Util::Renderer m_Root;

    bool showDemoWindow = true;

    int currentLevel = 0;
    int previousLevel = 0;

};

#endif