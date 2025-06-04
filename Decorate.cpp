//
// Created by Chucolate on 2025/5/23.
//
#include "Decorate.hpp"
#include "Util/Logger.hpp"
#include "Util/Renderer.hpp"


Decorate::Decorate()

    : m_BackGroundDecorate(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/mainUIexport_bUI2.png",
              "../assets/Texture2D/mainUIexport_fUI0001.png",//量條
          },
          false, 50, false, 1000)) {
    m_Transform.translation = {0 ,0}; // 初始化位置
    m_Transform.scale = {0.75f, 0.75f};
    m_BackGroundDecorate->SetFrameRange(0,1);
    SetDrawable(m_BackGroundDecorate);
    SetZIndex(5);
}