#include "MapManager.h"
#include <fstream>
#include <sstream>

bool MapManager::LoadMap(int level) {
    std::string filePath = "../assets/maps/test_map" + std::to_string(level) + ".txt";
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

std::vector<std::vector<int>>& MapManager::GetMapDataMutable() {
    return m_MapData;
}