#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <vector>
#include <string>

class MapManager {
public:

    bool LoadMap(int level);
    std::vector<std::vector<int>>& GetMapDataMutable();

private:
    std::vector<std::vector<int>> m_MapData;
};

#endif // MAPMANAGER_H