//
// Created by LAB 1222 on 2025/5/23.
//

#ifndef TRAP_H
#define TRAP_H
#include "Box.h"

class Trap : public Box {
public:
    Trap();
    void Update();
private:
    std::shared_ptr<Util::Animation> m_Animation;

};



#endif //TRAP_H
