#ifndef BEEL_FLY_H
#define BEEL_FLY_H

#include "../Util/Animation.hpp"
#include "../Util/GameObject.hpp"
#include "../pch.hpp"

class Beel_Fly : public Util::GameObject {
public:
    Beel_Fly();

    void Update();

private:
    std::shared_ptr<Util::Animation> m_Animation;
};

#endif // BEEL_FLY_H