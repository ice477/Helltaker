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
    return (m_MapData[y][x] == static_cast<int>(TileType::Empty));
}

void MapManager::PushBox(int x, int y, int newX, int newY) {
    if (CanMove(newX, newY)) {
        m_MapData[y][x] = static_cast<int>(TileType::Empty);
        m_MapData[newY][newX] = static_cast<int>(TileType::Box);
    }
}

std::pair<int, int> MapManager::GetPlayerInitialPosition() const {
    for (int y = 0; y < static_cast<int>(m_MapData.size()); y++) {
        for (int x = 0; x < static_cast<int>(m_MapData[y].size()); x++) {
            if (m_MapData[y][x] == static_cast<int>(TileType::Hero)) {
                return {x, y};
            }
        }
    }
    throw std::runtime_error("Player initial position not found in the map");
}

const std::vector<std::vector<int>>& MapManager::GetMapData() const {
    return m_MapData;
}