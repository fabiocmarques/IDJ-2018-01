//
// Created by Fabio Marques on 28/03/2018.
//

#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileHeight(tileHeight), tileWidth(tileWidth), rows(0), columns(0) {
    unique_ptr<GameObject> go(new GameObject());
    Sprite *spr = new Sprite(*go, file);
    tileSet = *spr;

    tileSet.Open(file);
}

void TileSet::RenderTile(unsigned int index, float x, float y) {

}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}
