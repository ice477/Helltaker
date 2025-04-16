#include "StageBG.h"
#include "Util/Logger.hpp"
#include "Util/Renderer.hpp"

StageBG::StageBG()

    : m_BackgroundAnimation(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/chapterBG0001.png",
              "../assets/Texture2D/chapterBG0002.png",
              "../assets/Texture2D/chapterBG0003.png",
              "../assets/Texture2D/chapterBG0004.png",
              "../assets/Texture2D/chapterBG0005.png",
              "../assets/Texture2D/chapterBG0006.png",
              "../assets/Texture2D/chapterBG0007.png",
              "../assets/Texture2D/chapterBG0008.png",
          },
          false, 50, false, 1000)) {
            m_Transform.translation = {0 ,0}; // 初始化位置
            m_Transform.scale = {0.75f, 0.75f};

    SetDrawable(m_BackgroundAnimation);
    SetZIndex(0);
}


void StageBG::Update() {

}