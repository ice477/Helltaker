#ifndef HERO_H
#define HERO_H
#include "pch.hpp"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class Hero : public Util::GameObject {
public:
    Hero();
    enum class State {
        DEFAULT,
        KICK,
        MOVE,
        WIN,
    };

    State m_State = State::DEFAULT;

    void Update();


private:
    std::shared_ptr<Util::Animation> m_Animation;

};
#endif // HERO_H