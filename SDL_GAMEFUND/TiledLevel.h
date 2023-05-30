#pragma once
#include <vector>
#include <map>
#include "GameObject.h"
class TileObject;

class TiledLevel :
    public GameObject
{
public :
    TiledLevel(int row, int cols, int tileWidth, int tileHeight,
        const char* tileData, const char* levelData, const char* tileKey);
    ~TiledLevel();
    void Update(float deltaTime) override;
    void Render() override;

private:
    const char* m_tileKey;
    int m_rows;
    int m_cols;

    //Our Map of 16 protoype TileObjectrs. From the Tiledata file
    std::map<char, TileObject*> m_tiles;
    std::vector<std::vector<TileObject*>> m_levelTiles; //2D Vector
    std::vector<TileObject*> m_obstacles;
};

