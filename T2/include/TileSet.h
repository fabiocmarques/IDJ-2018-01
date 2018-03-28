//
// Created by Fabio Marques on 28/03/2018.
//

#ifndef T2_TILESET_H
#define T2_TILESET_H

#include "Sprite.h"
#include <string>
using namespace std;

class TileSet {
    Sprite tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;

public:
    TileSet(int tileWidth, int tileHeight, string file);

    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();
};


#endif //T2_TILESET_H
