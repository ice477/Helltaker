//
// Created by Chucolate on 2025/6/1.
//
#include "game_item/Decoration.hpp"
#include "Util/Logger.hpp"
#include "Util/Renderer.hpp"

Decoration::Decoration()
    : m_Decoration(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/mainUIexport_bUI2.png",
              "../assets/Texture2D/mainUIexport_fUI0001.png",
          },
          false, 50, false, 1000)) {
    m_Transform.translation = {-500 ,-150}; // 初始化位置//-450, -100
    m_Transform.scale = {0.6f, 0.6f};//0.75f,0.75f
    m_Decoration->SetFrameRange(0,1);
    SetDrawable(m_Decoration);
    SetZIndex(7);
}
DecorationRight::DecorationRight()
    : m_DecorationRight(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/mainUIexport_bUI2.png",
              "../assets/Texture2D/mainUIexport_fUI0001.png",
          },
          false, 50, false, 1000)) {
    m_Transform.translation = {500 ,-150}; // 初始化位置//-450, -100
    m_Transform.scale = {-0.6f, 0.6f};//0.75f,0.75f
    m_DecorationRight->SetFrameRange(0,1);
    SetDrawable(m_DecorationRight);
    SetZIndex(7);
}
DecorateLeft::DecorateLeft()
    : m_DecorateLeft(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/mainUIexport_bUI2.png",
              "../assets/Texture2D/mainUIexport_fUI0001.png",
          },
          false, 50, false, 1000)) {
    m_Transform.translation = {-550 ,150}; // 初始化位置//-450, -100
    m_Transform.scale = {0.7f, 0.7f};//0.75f,0.75f
    m_DecorateLeft->SetFrameRange(0,1);
    SetDrawable(m_DecorateLeft);
    SetZIndex(5);
}
DecorateRight::DecorateRight()
    : m_DecorateRight(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              "../assets/Texture2D/mainUIexport_bUI2.png",
              "../assets/Texture2D/mainUIexport_fUI0001.png",
          },
          false, 50, false, 1000)) {
    m_Transform.translation = {550 ,150}; // 初始化位置//-450, -100
    m_Transform.scale = {-0.7f, 0.7f};//0.75f,0.75f
    m_DecorateRight->SetFrameRange(0,1);
    SetDrawable(m_DecorateRight);
    SetZIndex(5);
}

//StepCount::StepCount()
//Dec_Level::Dec_Level()

void Decoration::Update() {
    m_Decoration->SetCurrentFrame(1);
}
void DecorationRight::Update() {
    m_DecorationRight->SetCurrentFrame(1);
}
void DecorateLeft::Update() {
    m_DecorateLeft->SetCurrentFrame(0);
}
void DecorateRight::Update() {
    m_DecorateRight->SetCurrentFrame(0);
}
