
#include "Hero.h"


Hero::Hero()
    : m_Animation(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              //DEFAULT
              "../assets/Texture2D/hero0022.png","../assets/Texture2D/hero0023.png","../assets/Texture2D/hero0024.png","../assets/Texture2D/hero0025.png",
              "../assets/Texture2D/hero0026.png","../assets/Texture2D/hero0027.png",

              //DEFAULT
              "../assets/Texture2D/assets100V20053.png","../assets/Texture2D/assets100V20054.png","../assets/Texture2D/assets100V20055.png","../assets/Texture2D/assets100V20056.png",
              "../assets/Texture2D/assets100V20057.png","../assets/Texture2D/assets100V20058.png",

              //kick
              "../assets/Texture2D/hero0028.png","../assets/Texture2D/hero0029.png","../assets/Texture2D/hero0030.png","../assets/Texture2D/hero0031.png",
              "../assets/Texture2D/hero0032.png","../assets/Texture2D/hero0033.png","../assets/Texture2D/hero0034.png","../assets/Texture2D/hero0035.png",
              "../assets/Texture2D/hero0036.png","../assets/Texture2D/hero0037.png","../assets/Texture2D/hero0038.png","../assets/Texture2D/hero0039.png",
              "../assets/Texture2D/hero0040.png","../assets/Texture2D/hero0041.png","../assets/Texture2D/hero0042.png","../assets/Texture2D/hero0043.png",
              "../assets/Texture2D/hero0044.png","../assets/Texture2D/hero0045.png","../assets/Texture2D/hero0046.png","../assets/Texture2D/hero0047.png",
              "../assets/Texture2D/hero0048.png","../assets/Texture2D/hero0049.png",

              //win
              "../assets/Texture2D/hero0050.png","../assets/Texture2D/hero0051.png","../assets/Texture2D/hero0052.png","../assets/Texture2D/hero0053.png",
              "../assets/Texture2D/hero0054.png","../assets/Texture2D/hero0055.png","../assets/Texture2D/hero0056.png","../assets/Texture2D/hero0057.png",
              "../assets/Texture2D/hero0058.png","../assets/Texture2D/hero0059.png","../assets/Texture2D/hero0060.png","../assets/Texture2D/hero0061.png",
              "../assets/Texture2D/hero0062.png","../assets/Texture2D/hero0063.png","../assets/Texture2D/hero0064.png","../assets/Texture2D/hero0065.png",
              "../assets/Texture2D/hero0066.png","../assets/Texture2D/hero0067.png","../assets/Texture2D/hero0068.png","../assets/Texture2D/hero0069.png",
              "../assets/Texture2D/hero0070.png","../assets/Texture2D/hero0071.png","../assets/Texture2D/hero0072.png","../assets/Texture2D/hero0073.png",
              "../assets/Texture2D/hero0074.png","../assets/Texture2D/hero0075.png","../assets/Texture2D/hero0076.png","../assets/Texture2D/hero0077.png",          },
          true, 50, false, 1000)) {


    m_Transform.translation = {0 ,110}; // 初始化位置
    m_Transform.scale = {0.65f, 0.65f}; // 初始化縮放
    m_Transform.rotation = 0.0f; // 初始化旋轉角度
    SetDrawable(m_Animation);
    SetZIndex(5);
}

void Hero::Update() {
    // Update logic for Hero


}