#pragma once
#include <vector>
#include <map>
#include "GameObject.h"
#include "TileObject.h"

class TiledLevel :
    public GameObject
{
public :
    TiledLevel(int row, int cols, int tileWidth, int tileHeight,
        const char* tileData, const char* levelData, const char* tileKey);
    ~TiledLevel();
    virtual void Update([[maybe_unused]] float deltaTime) override;
    virtual void Render() override;


    std::vector<Tile*>& GetObstacles() { return m_obstacles; }

private:
    const char* m_tileKey;
    int m_rows;
    int m_cols;

    //Our Map of 16 protoype TileObjectrs. From the Tiledata file
    std::map<char, Tile*> m_tiles;
    std::vector<std::vector<Tile*>> m_levelTiles; //2D Vector
    std::vector<Tile*> m_obstacles;
};

