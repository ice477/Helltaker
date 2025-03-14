#ifndef BEEL_FLY_H
#define BEEL_FLY_H

#include "pch.hpp"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class Beel_Fly : public Util::GameObject {
public:
    Beel_Fly();
    void Update();

private:
    std::shared_ptr<Util::Animation> beel_fly;
};

#endif // BEEL_FLY_H