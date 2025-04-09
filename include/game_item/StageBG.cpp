#include "StageBG.h"
#include "Util/Logger.hpp"

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
          true, 100, true, 1)) {}


void StageBG::Update() {

}