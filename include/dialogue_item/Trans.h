//
// Created by sue bo  shuan on 25-4-18.
//

#ifndef TRANS_H
#define TRANS_H

#include "../Util/Animation.hpp"
#include "../Util/GameObject.hpp"
#include "../pch.hpp"

class Trans : public Util::GameObject {
public:
    Trans();
    void Update();

private:
    std::shared_ptr<Util::Animation> m_Animation;
    bool m_IsPlaying = false;
};

#endif
