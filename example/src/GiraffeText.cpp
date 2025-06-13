#include "GiraffeText.hpp"

#include "Util/Color.hpp"
#include "Util/Time.hpp"

void GiraffeText::Start() {
    m_Text = std::make_unique<Util::Text>(m_Font, m_Size, "0",
                                          Util::Color::FromRGB(255, 255, 255));
    SetDrawable(m_Text);
}

void GiraffeText::Update() {
    m_Text->SetColor(Util::Color::FromName(Util::Colors::WHITE));
}
