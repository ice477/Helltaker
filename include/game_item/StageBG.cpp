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


void StageBG::Update(int level) {
    if (level == 1 ||  level == 9 ||  level == 20  || level == 30) {
     m_BackgroundAnimation->SetCurrentFrame(0);
    }
    else if (level == 2 || level == 13 || level == 29) {
        m_BackgroundAnimation->SetCurrentFrame(1);
    }
    else if (level == 3 || level == 10 || level == 28) {
        m_BackgroundAnimation->SetCurrentFrame(2);
    }
    else if (level == 4 || level == 14 || level == 16 || level == 27) {
        m_BackgroundAnimation->SetCurrentFrame(3);
    }
    else if (level == 5 || level == 11 || level == 22 || level == 26) {
        m_BackgroundAnimation->SetCurrentFrame(4);
    }
    else if (level == 6 || level == 15 || level == 17 || level == 25) {
        m_BackgroundAnimation->SetCurrentFrame(5);
    }
    else if (level == 7 || level == 12 || level == 18 || level == 21 || level == 24) {
        m_BackgroundAnimation->SetCurrentFrame(6);
    }
    else if (level == 8 || level == 19 || level == 23 ) {
        m_BackgroundAnimation->SetCurrentFrame(7);
    }
}
