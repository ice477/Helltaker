#include "DialogueBox.h"

#include "Util/Animation.hpp"
#include "Util/Logger.hpp"

DialogueBox::DialogueBox()
    :dialogueBox(std::make_shared<Util::Animation>(
        std::vector<std::string>{
            "../assets/Texture2D/dialogueBG_abyss.png",
            "../assets/Texture2D/dialogueBG_abyss02.png",
        },
        true, 50, false, 1000)) {

void DialogueBox::SetText(const std::string& text) {
    m_Text->SetText(text);
}

void DialogueBox::Update() {
    // Update logic for DialogueBox if needed
}