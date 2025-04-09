#ifndef WALL_H
#define WALL_H

#include "pch.hpp"
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"

class Wall : public Util::GameObject {
public:
    Wall();
    
    enum class Type {
        NORMAL,

    };
    
    void SetType(Type type);
    Type GetType() const;
    
    void Update();

private:
    Type m_Type = Type::NORMAL;
    std::shared_ptr<Util::Animation> m_Animation; // 可選，如果牆體有不同外觀
    bool m_IsActive = true;
};

#endif //WALL_H