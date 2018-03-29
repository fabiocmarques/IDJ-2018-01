//
// Created by fabio on 28/03/18.
//

#ifndef T2_TILEMAP_H
#define T2_TILEMAP_H


#include "Component.h"
#include "TileSet.h"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class TileMap : public Component {
    vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;

public:
    TileMap(GameObject& associated, string file, TileSet* tileSet);
    void Load(string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);

    void Render() override;
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

    int GetWidth();
    int GetHeight();
    int GetDepth();
};


#endif //T2_TILEMAP_H
