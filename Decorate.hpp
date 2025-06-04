//
// Created by Chucolate on 2025/5/23.
//

#ifndef DECORATE_HPP
#define DECORATE_HPP

#include "../Util/Animation.hpp"
#include "../Util/GameObject.hpp"
#include "../pch.hpp"
#include <memory>


class Decorate : public Util::GameObject {
public:
    Decorate();
    void Update(int level);

private:
    std::shared_ptr<Util::Animation> m_BackGroundDecorate;
};

#endif
//DECORATE_HPP
