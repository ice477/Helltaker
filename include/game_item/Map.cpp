// Map.cpp
#include "Map.h"
#include "../Util/Input.hpp"
#include "../Util/Keycode.hpp"
#include "../Util/Renderer.hpp"
#include <fstream>
#include <iostream>

Map::Map(const std::string& mapFile) {
    LoadMap(mapFile);
    m_Animation = std::make_shared<Util::Animation>(
        std::vector<std::string>{
            "../assets/Texture2D/empty.png",
            "../assets/Texture2D/wall.png",
            "../assets/Texture2D/box.png",
            "../assets/Texture2D/target.png",
            "../assets/Texture2D/player.png",
        },
        true, 50, false, 1000);
}

void Map::LoadMap(const std::string& mapFile) {
    std::ifstream file(mapFile);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << mapFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char ch : line) {
            switch (ch) {
            case ' ': row.push_back(0); break; // EMPTY
            case '#': row.push_back(1); break; // WALL
            case 'B': row.push_back(2); break; // BOX
            case 'T': row.push_back(3); break; // TARGET
            case 'P': row.push_back(4); break; // PLAYER
            case 'E': row.push_back(5); break; //ENEMY
            default: row.push_back(0); break; // EMPTY
            }
        }
        m_MapData.push_back(row);
    }
}

void Map::Update() {
    // 假設玩家位置為 (playerX, playerY)
    int playerX = 0, playerY = 0;
    for (int y = 0; y < m_MapData.size(); ++y) {
        for (int x = 0; x < m_MapData[y].size(); ++x) {
            if (m_MapData[y][x] == 4) { // PLAYER
                playerX = x;
                playerY = y;
                break;
            }
        }
    }

    // 處理玩家輸入
    if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
        // 向上移動
        if (m_MapData[playerY - 1][playerX] == 0) { // MEET EMPTY
            m_MapData[playerY][playerX] = 0;
            m_MapData[playerY - 1][playerX] = 4;
        }
        else if (m_MapData[playerY - 1][playerX] == 2) { // MEET BOX
            if (m_MapData[playerY - 2][playerX] == 0) {  // BOX MOVE
                m_MapData[playerY - 2][playerX] = 2;
            }
        }
        else if (m_MapData[playerY - 1][playerX] == 3) { // MEET TARGET
            // 處理遇到目標的邏輯
        }
        else if (m_MapData[playerY - 1][playerX] == 5) { // MEET ENEMY
            if (m_MapData[playerY - 2][playerX] == 0) {  //ENEMY MOVE
                m_MapData[playerY - 2][playerX] = 5;
                m_MapData[playerY - 1][playerX] = 0;
            }
            else if (m_MapData[playerY - 2][playerX] == 1 || m_MapData[playerY - 2][playerX] == 2 || m_MapData[playerY - 2][playerX] == 5) {  //ENEMY BREAK
                m_MapData[playerY - 1][playerX] = 0;
            }
        }
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
        // 向下移動
        if (m_MapData[playerY + 1][playerX] == 0) {
            m_MapData[playerY][playerX] = 0;
            m_MapData[playerY + 1][playerX] = 4;
        } else if (m_MapData[playerY + 1][playerX] == 2) {
            if (m_MapData[playerY + 2][playerX] == 0) {
                m_MapData[playerY + 2][playerX] = 2;
            }
        } else if (m_MapData[playerY + 1][playerX] == 3) {
            // 處理遇到目標的邏輯
        } else if (m_MapData[playerY + 1][playerX] == 5) {
            if (m_MapData[playerY + 2][playerX] == 0) {
                m_MapData[playerY + 2][playerX] = 5;
                m_MapData[playerY + 1][playerX] = 0;
            } else if (m_MapData[playerY + 2][playerX] == 1 || m_MapData[playerY + 2][playerX] == 2 || m_MapData[playerY + 2][playerX] == 5) {
                m_MapData[playerY + 1][playerX] = 0;
            }
        }
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
        // 向左移動
        if (m_MapData[playerY][playerX - 1] == 0) {
            m_MapData[playerY][playerX] = 0;
            m_MapData[playerY][playerX - 1] = 4;
        } else if (m_MapData[playerY][playerX - 1] == 2) {
            if (m_MapData[playerY][playerX - 2] == 0) {
                m_MapData[playerY][playerX - 2] = 2;
            }
        } else if (m_MapData[playerY][playerX - 1] == 3) {
            // 處理遇到目標的邏輯
        } else if (m_MapData[playerY][playerX - 1] == 5) {
            if (m_MapData[playerY][playerX - 2] == 0) {
                m_MapData[playerY][playerX - 2] = 5;
                m_MapData[playerY][playerX - 1] = 0;
            } else if (m_MapData[playerY][playerX - 2] == 1 || m_MapData[playerY][playerX - 2] == 2 || m_MapData[playerY][playerX - 2] == 5) {
                m_MapData[playerY][playerX - 1] = 0;
            }
        }
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
        // 向右移動
        if (m_MapData[playerY][playerX + 1] == 0) {
            m_MapData[playerY][playerX] = 0;
            m_MapData[playerY][playerX + 1] = 4;
        } else if (m_MapData[playerY][playerX + 1] == 2) {
            if (m_MapData[playerY][playerX + 2] == 0) {
                m_MapData[playerY][playerX + 2] = 2;
            }
        } else if (m_MapData[playerY][playerX + 1] == 3) {
            // 處理遇到目標的邏輯
        } else if (m_MapData[playerY][playerX + 1] == 5) {
            if (m_MapData[playerY][playerX + 2] == 0) {
                m_MapData[playerY][playerX + 2] = 5;
                m_MapData[playerY][playerX + 1] = 0;
            } else if (m_MapData[playerY][playerX + 2] == 1 || m_MapData[playerY][playerX + 2] == 2 || m_MapData[playerY][playerX + 2] == 5) {
                m_MapData[playerY][playerX + 1] = 0;
            }
        }
    }
}



const std::vector<std::vector<int>>& Map::GetMapData() const {
    return m_MapData;
}