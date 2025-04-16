#ifndef BEEL_FLY_H
#define BEEL_FLY_H

#include "../Util/Animation.hpp"
#include "../Util/GameObject.hpp"
#include "../pch.hpp"

class Character : public Util::GameObject {
public:
    Character();

    void Update();

private:
    std::shared_ptr<Util::Animation> m_Animation;
};

#endif // BEEL_FLY_H