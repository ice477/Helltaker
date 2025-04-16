#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"

#include "Cat.hpp"
#include "Giraffe.hpp"
#include "GiraffeText.hpp"
#include "dialogue_item/Character.h"
#include "game_item/StageBG.h"
#include "game_item/Hero.h"

class App {
public:
    enum class State {
        START,
        UPDATE,
        PUSH_BOX,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

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

    std::shared_ptr<Character> m_Character = std::make_shared<Character>();

    std::shared_ptr<StageBG> m_StageBG = std::make_shared<StageBG>();

    std::shared_ptr<Hero> m_Hero = std::make_shared<Hero>();

    Util::Renderer m_Root;

    bool showDemoWindow = true;

    int currentLevel = 0;
    int previousLevel = 0;
};

#endif