// Gate.cpp
#include "Gate.h"

Gate::Gate() {
    m_Animation = std::make_shared<Util::Animation>(
        std::vector<std::string>{"../assets/Texture2D/backup_lockbox.png",
        },
        false, 50, false, 100);
    m_Transform.scale = {0.75f, 0.75f};
    m_Transform.translation = {75 ,100};
    SetDrawable(m_Animation);
    SetZIndex(5);
}

void Gate::Update() {
    // 更新動畫
    if (m_Animation) {
        m_Animation->Play();
    }
}