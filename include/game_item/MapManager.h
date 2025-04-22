#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <vector>
#include <string>

class MapManager {
public:
    enum class TileType {
        Empty = 0,  // 0空地
        Wall,       // 1牆
        Box,        // 2箱子
        Enemy,      // 3敵人
        Door,       // 4門
        Key,        // 5 鑰匙
        Target,      // 6目標
        Player,     // 7 玩家
    };

    bool LoadMap(const std::string& filePath);
    bool CanMove(int x, int y) const;
    void PushBox(int x, int y, int newX, int newY);

    std::pair<int,int> GetPlayerInitialPosition() const;
    const std::vector<std::vector<int>>& GetMapData() const;

private:
    std::vector<std::vector<int>> m_MapData;

};

#endif // MAPMANAGER_H