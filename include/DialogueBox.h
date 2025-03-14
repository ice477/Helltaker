#ifndef DIALOGUE_BOX_H
#define DIALOGUE_BOX_H

#include "pch.hpp"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class DialogueBox : public Util::GameObject {
public:
    DialogueBox();
    void SetText(const std::string& text);
    void Update();

private:
    std::shared_ptr<Util::Text> m_Text;
};

#endif // DIALOGUE_BOX_H