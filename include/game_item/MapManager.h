#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <vector>
#include <string>

class MapManager {
public:
    enum class TileType {
        Empty = 0,  // 0空地
        Wall = 1,
        Hero = 2,
        Box = 3,
        Enemy = 4,
        Gate = 5,
        Key = 6,
        Target = 7,
    };

    bool LoadMap(const std::string& filePath);
    const std::vector<std::vector<int>>& GetMapData() const;

private:
    std::vector<std::vector<int>> m_MapData;

};

#endif // MAPMANAGER_H