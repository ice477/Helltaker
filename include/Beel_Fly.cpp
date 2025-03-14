#include "Beel_Fly.h"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"

Beel_Fly::Beel_Fly()
    : beel_fly(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/beel_fly_portal.png",
              "../assets/Texture2D/beel_fly.png",
          },
          true, 50, false, 1000)) {
    SetDrawable(beel_fly);
}

void Beel_Fly::Update() {
    // Update logic for Beel_Fly
}