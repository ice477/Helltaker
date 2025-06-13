//
// Created by sue bo  shuan on 25-4-18.
//

#ifndef TRANS_H
#define TRANS_H

#include "../Util/Animation.hpp"
#include "../Util/GameObject.hpp"
#include "../pch.hpp"
#include "../game_item/Hero.h"

enum class State;


class Trans : public Util::GameObject {
public:
    Trans();
    void Update(State appState, bool textEnd) ;
    std::shared_ptr<Util::Animation> m_Animation;

private:
    std::shared_ptr<Hero> m_Hero = std::make_shared<Hero>();
};

#endif
