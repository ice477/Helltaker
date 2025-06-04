#ifndef DIALOGUE_BOX_H
#define DIALOGUE_BOX_H

#include "../Util/Animation.hpp"
#include "../Util/GameObject.hpp"
#include "../Util/Text.hpp"
#include "../pch.hpp"

class DialogueBG : public Util::GameObject {
public:
    DialogueBG();
    // void SetText(const std::string& text);
    void Update();

private:
    std::shared_ptr<Util::Animation> dialogueBG;
};

#endif // DIALOGUE_BOX_H