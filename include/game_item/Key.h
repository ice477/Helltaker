//
// Created by sue bo  shuan on 25-4-18.
//

#ifndef KEY_H
#define KEY_H

#include "Box.h"

class Key : public Box {
public:
    Key();
    void Update();
private:
    std::shared_ptr<Util::Animation> m_Animation;

};

#endif

