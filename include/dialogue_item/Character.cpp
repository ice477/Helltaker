#include "Character.h"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"

Character::Character()
    : m_Animation(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/beel_fly_portal.png",
              "../assets/Texture2D/beel_fly.png",
          },
          false, 50, false, 1000)) {
    m_Transform.translation = {0 ,110}; // 初始化位置
    m_Transform.scale = {0.65f, 0.65f}; // 初始化縮放
    m_Transform.rotation = 0.0f; // 初始化旋轉角度
    SetDrawable(m_Animation);
    SetZIndex(5);
    SetVisible(false);
    m_Animation->SetFrameRange(0, 1); // 設置動畫範圍
}

void Character::Update() {

}