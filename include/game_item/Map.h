#ifndef MAP_H
#define MAP_H

#include "../Util/Animation.hpp"
#include <memory>
#include <string>
#include <vector>

class Map {
public:
    Map(const std::string& filePath);
    void Update();
    const std::vector<std::vector<int>>& GetMapData() const;

private:
    void LoadMap(const std::string& filePath);
    std::vector<std::vector<int>> m_MapData;
    std::shared_ptr<Util::Animation> m_Animation;
};

#endif // MAP_H