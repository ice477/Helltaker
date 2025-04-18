#include "../dialogue_item/DialogueBG.h"

#include "../Util/Input.hpp"
#include "../Util/Logger.hpp"
#include "../config.hpp"

DialogueBG::DialogueBG()
    : dialogueBG (std::make_shared<Util::Animation>(
        std::vector<std::string>{
            "../assets/Texture2D/dialogueBG_abyss.png",
            "../assets/Texture2D/dialogueBG_abyss02.png",
            "../assets/Texture2D/dialogueBG_abyss02Grad.png",
            "../assets/Texture2D/dialogueBG_home.png",
            "../assets/Texture2D/dialogueBG_throne2.png",
            "../assets/Texture2D/dialogueBG_sin.png",
            "../assets/Texture2D/dialogueBG_sinM2.png",
            "../assets/Texture2D/dialogueBG_hell.png",

        },
      false, 50, false, 1000)) {
    m_Transform.translation = {0, 60};
    m_Transform.scale = {1, 0.7f};
    SetDrawable(dialogueBG);
    SetZIndex(1);
}


void DialogueBG::Update() {
    // Update logic for DialogueBox if needed
    m_Transform.translation.x += 1;

    if (m_Transform.translation.x >= static_cast<float>(PTSD_Config::WINDOW_WIDTH)-1016) {
        if (dialogueBG->GetCurrentFrameIndex() == 0) {
            dialogueBG->SetCurrentFrame(1);
        } else if (dialogueBG->GetCurrentFrameIndex() == 1) {
            dialogueBG->SetCurrentFrame(0);
        }
        m_Transform.translation.x = 0;

    }

}