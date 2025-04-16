#include "Box.h"

Box::Box() {
    m_Animation = std::make_shared<Util::Animation>(
        std::vector<std::string>{"../assets/Texture2D/boxExport0001.png", "../assets/Texture2D/boxExport0002.png", "../assets/Texture2D/boxExport0003.png",
                                 "../assets/Texture2D/boxExport0004.png", "../assets/Texture2D/boxExport0005.png", "../assets/Texture2D/boxExport0006.png",
                                 "../assets/Texture2D/boxExport0007.png", "../assets/Texture2D/boxExport0008.png", "../assets/Texture2D/boxExport0009.png",
                                 "../assets/Texture2D/boxExport0010.png", "../assets/Texture2D/boxExport0011.png",
        },
        false, 50, false, 100);

    SetDrawable(m_Animation);
    SetZIndex(4);
}

void Box::Update() {
    // 更新動畫
    if (m_Animation) {
        m_Animation->Play();
    }
}

bool Box::Push(const glm::vec2& direction) {
    if (!CheckObstacle(direction)) {
        m_Transform.translation += direction * 75.0f; // 推動距離
        return true;
    }
    return false;
}

bool Box::CheckObstacle(const glm::vec2& direction) {
    // 簡單檢查是否超出邊界
    glm::vec2 newPosition = m_Transform.translation + direction * 75.0f;
    return (newPosition.x < 0 || newPosition.y < 0 || newPosition.x > 800 || newPosition.y > 600);
}