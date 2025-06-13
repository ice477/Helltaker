//
// Created by 蘇柏瑄 on 2025/6/13.
//

#ifndef BUTTON_H
#define BUTTON_H

#include "../Util/Animation.hpp"
#include "../Util/GameObject.hpp"
#include "../Util/image.hpp"
#include "../pch.hpp"

class Button : public Util::GameObject {
public:
    Button();

    void Update();

private:
    std::shared_ptr<Util::Animation> m_Animation;
};

#endif //BUTTON_H
