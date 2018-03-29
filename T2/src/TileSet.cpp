//
// Created by Fabio Marques on 28/03/2018.
//

#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileHeight(tileHeight), tileWidth(tileWidth), rows(0), columns(0), tileSet(*new GameObject(), file) {

    tileSet.Open(file);

    if(!tileSet.IsOpen()){
        cout << "Error on open file: \"" << file << "\" on TileSet.";
        exit(1);
    }

    rows = tileSet.GetHeight()/tileHeight;
    columns = tileSet.GetWidth()/tileWidth;

}

void TileSet::RenderTile(unsigned int index, float x, float y) {
    int mIndex = rows*columns;
    int tX, tY;

    if(index >= mIndex){
        cout << "Invalid index (" << index << "), max index: " << (mIndex- 1);
        exit(1);
    }

    tY = index/rows;
    tX = index%rows;

    tileSet.SetClip(tX, tY, tileWidth, tileHeight);
    tileSet.Render(x, y);
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}
