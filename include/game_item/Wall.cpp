#include "Wall.h"

Wall::Wall()
    : m_Animation(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/assets100V20081.png"},
              true, 50, false, 1000)) {


    m_Transform.translation = {0 ,110}; // 初始化位置
    m_Transform.scale = {0.65f, 0.65f}; // 初始化縮放
    m_Transform.rotation = 0.0f; // 初始化旋轉角度
    SetDrawable(m_Animation);
    SetZIndex(5);
}



void Wall::SetType(Wall::Type type) {
    m_Type = type;
    // 根據不同類型設置不同的外觀或屬性
}

Wall::Type Wall::GetType() const {
    return m_Type;
}

void Wall::Update() {

}