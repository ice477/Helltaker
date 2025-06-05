//
// Created by Chucolate on 2025/6/1.
//

#ifndef DECORATION_HPP
#define DECORATION_HPP

#include "../Util/Animation.hpp"
#include "../Util/GameObject.hpp"
#include "../pch.hpp"
//#include <memory>


class Decoration : public Util::GameObject {
public:
    Decoration();
    void Update();

private:
    std::shared_ptr<Util::Animation> m_Decoration;
};

class DecorationRight : public Util::GameObject {
public:
    DecorationRight();
    void Update();
private:
    std::shared_ptr<Util::Animation> m_DecorationRight;
};

class DecorateLeft : public Util::GameObject {
public:
    DecorateLeft();
    void Update();
private:
    std::shared_ptr<Util::Animation> m_DecorateLeft;
};

class DecorateRight : public Util::GameObject {
public:
    DecorateRight();
    void Update();
private:
    std::shared_ptr<Util::Animation> m_DecorateRight;
};
#endif //DECORATION_HPP
