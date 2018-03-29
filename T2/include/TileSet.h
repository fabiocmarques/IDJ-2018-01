//
// Created by Fabio Marques on 28/03/2018.
//

#ifndef T2_TILESET_H
#define T2_TILESET_H

#define TILE_WIDTH 64
#define TILE_HEIGHT 64

#include "Sprite.h"
#include <string>
#include <iostream>

using namespace std;

class TileSet {
    Sprite tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;

public:
    TileSet(int tileWidth, int tileHeight, string file);
    ~TileSet();

    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();
};


#endif //T2_TILESET_H
