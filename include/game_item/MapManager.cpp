#include "MapManager.h"
#include <fstream>
#include <sstream>

bool MapManager::LoadMap(const std::string& filePath) {
    std::ifstream file(filePath);
    if(!file.is_open()) return false;

    m_MapData.clear();
    std::string line;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<int> row;
        int value;
        while(ss >> value) {
            row.push_back(value);
        }
        m_MapData.push_back(row);
    }
    return true;
}

bool MapManager::CanMove(int x, int y) const {
    if(x < 0 || y < 0 || y >= static_cast<int>(m_MapData.size()) ||
       x >= static_cast<int>(m_MapData[y].size())) {
        return false;
       }
    return (m_MapData[y][x] == 0);
}

void MapManager::PushBox(int x, int y, int newX, int newY) {
    if(CanMove(newX, newY)) {
        // 0 為可走, 1 為障礙, 2 為箱子
        m_MapData[y][x] = 0;
        m_MapData[newY][newX] = 2;
    }
}

std::pair<int,int> MapManager::GetPlayerInitialPosition() const {
    for (int y = 0; y < static_cast<int>(m_MapData.size()); y++) {
        for (int x = 0; x < static_cast<int>(m_MapData[y].size()); x++) {
            if (m_MapData[y][x] == static_cast<int>(TileType::Player)) {
                return {x, y};
            }
        }
    }
    return {0, 0};
}