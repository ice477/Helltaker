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



const std::vector<std::vector<int>>& MapManager::GetMapData() const {
    return m_MapData;
}