#ifndef STAGEBG_H
#define STAGEBG_H

#include "../Util/Animation.hpp"
#include <memory>
#include <string>
#include <vector>

class StageBG {
public:
    StageBG();
    void Update();

private:
    std::shared_ptr<Util::Animation> m_BackgroundAnimation;
};

#endif