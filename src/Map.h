//
// Created by Kelvin on 20/06/2020.
//

#ifndef ENGINE2D_MAP_H
#define ENGINE2D_MAP_H

#include <string>

class Map {
private:
    std::string textureName;
    int scale;
    int tileSize;
public:
    Map(std::string textureName, int scale, int tileSize);
    ~Map();
    void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
    void AddTile(int sourceX, int sourceY, int x, int y);
};


#endif //ENGINE2D_MAP_H
