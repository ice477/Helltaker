#ifndef STAGEBG_H
#define STAGEBG_H

#include "../Util/Animation.hpp"
#include "../Util/GameObject.hpp"
#include "../pch.hpp"
#include <memory>


class StageBG : public Util::GameObject {
public:
    StageBG();
    void Update();

private:
    std::shared_ptr<Util::Animation> m_BackgroundAnimation;
};

#endif