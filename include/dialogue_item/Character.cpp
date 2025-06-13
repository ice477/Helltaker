#include "Character.h"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "Util/image.hpp"

Character::Character()
    : m_Animation(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/beel_fly.png",
              "../assets/Texture2D/pand_idle.png",
              "../assets/Texture2D/pand_cup.png",
              "../assets/Texture2D/pand_drink.png",
              "../assets/Texture2D/pand_flust.png",
              "../assets/Texture2D/mod_idle.png",
              "../assets/Texture2D/mod_book.png",
              "../assets/Texture2D/mod_close.png",
              "../assets/Texture2D/mod_shy.png",
              "../assets/Texture2D/cer_idle.png",
              "../assets/Texture2D/cer_bad.png",
              "../assets/Texture2D/cer_happy.png",
              "../assets/Texture2D/mal_idle.png",
              "../assets/Texture2D/mal_bottle.png",
              "../assets/Texture2D/mal_prebottle.png",
              "../assets/Texture2D/mal_phone.png",
              "../assets/Texture2D/mal_puzzled.png",
              "../assets/Texture2D/z_idle.png",
              "../assets/Texture2D/z_ignite1.png",
              "../assets/Texture2D/z_ignite2.png",
              "../assets/Texture2D/z_ignite3.png",
              "../assets/Texture2D/z_ignite4.png",
              "../assets/Texture2D/z_laugh.png",
              "../assets/Texture2D/z_snap.png",
              "../assets/Texture2D/az_idle.png",
              "../assets/Texture2D/az_note.png",
              "../assets/Texture2D/az_shock.png",
              "../assets/Texture2D/jus_idle.png",
              "../assets/Texture2D/jus_blind.png",
              "../assets/Texture2D/jus_curious.png",
              "../assets/Texture2D/jus_pc.png",
              "../assets/Texture2D/LH_idle.png",
              "../assets/Texture2D/LH_happy.png",
              "../assets/Texture2D/LH_rustled.png",
              "../assets/Texture2D/LH_swirl (1).png",
              "../assets/Texture2D/LH_swirl (2).png",
              "../assets/Texture2D/LH_swirl (3).png",
              "../assets/Texture2D/LH_swirl (4).png",
              "../assets/Texture2D/LH_swirl (5).png",
              "../assets/Texture2D/LH_angry.png",



          },
          true, 100, true, 100)) {

    m_Transform.translation = {0 ,110}; // 初始化位置
    m_Transform.scale = {0.7f, 0.7f}; // 初始化縮放
    m_Transform.rotation = 0.0f; // 初始化旋轉角度
    SetDrawable(m_Animation);
    SetZIndex(5);
    SetVisible(false);
}

void Character::Update(int level) {
    m_Animation->Play();
    switch (level) {
    case 0:  m_Animation->SetCurrentFrame(0);  break;
    case 1:  m_Animation->SetCurrentFrame(1);  break;
    case 2:  m_Animation->SetCurrentFrame(5);  break;
    case 3:  m_Animation->SetCurrentFrame(9);  break;
    case 4:  m_Animation->SetCurrentFrame(12); break;
    case 5:  m_Animation->SetCurrentFrame(17); break;
    case 6:  m_Animation->SetCurrentFrame(24); break;
    case 7:  m_Animation->SetCurrentFrame(27); break;
    case 8:  m_Animation->SetCurrentFrame(31); break;
    case 9:  m_Animation->SetCurrentFrame(2);  break;
    case 10: m_Animation->SetCurrentFrame(6);  break;
    case 11: m_Animation->SetCurrentFrame(10);  break;
    case 12: m_Animation->SetFrameRange(13,14);  break;
    case 13: m_Animation->SetFrameRange(18,21);  break;
    case 14: m_Animation->SetCurrentFrame(25);  break;
    case 15: m_Animation->SetCurrentFrame(28); break;
    case 16: m_Animation->SetFrameRange(34,38); break;
    case 17: m_Animation->SetCurrentFrame(3); break;
    case 18: m_Animation->SetCurrentFrame(7); break;
    case 19: m_Animation->SetCurrentFrame(11); break;
    case 20: m_Animation->SetCurrentFrame(15); break;
    case 21: m_Animation->SetCurrentFrame(22); break;
    case 22: m_Animation->SetCurrentFrame(26); break;
    case 23: m_Animation->SetCurrentFrame(29); break;
    case 24: m_Animation->SetCurrentFrame(32); break;
    case 25: m_Animation->SetCurrentFrame(4); break;
    case 26: m_Animation->SetCurrentFrame(8); break;
    case 27: m_Animation->SetCurrentFrame(9); break;
    case 28: m_Animation->SetCurrentFrame(16); break;
    case 29: m_Animation->SetCurrentFrame(23); break;
    case 30: m_Animation->SetCurrentFrame(24); break;
    default:
        // 預設處理
        break;
    }
}