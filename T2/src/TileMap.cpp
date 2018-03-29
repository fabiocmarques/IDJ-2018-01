//
// Created by fabio on 28/03/18.
//

#include "TileMap.h"

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) : Component(associated),
                                                                          tileSet(tileSet), mapDepth(0),
                                                                          mapHeight(0), mapWidth(0),
                                                                          tileMatrix(*new vector<int>()) {

    Load(file);
}

void TileMap::Load(string file) {
    int i, j, k = 0, p;
    char buff;
    ifstream myfile(file);

    if (myfile.is_open()) {
        myfile >> mapWidth;
        myfile >> buff;
        myfile >> mapHeight;
        myfile >> buff;
        myfile >> mapDepth;
        myfile >> buff;

        for (k = 0; k < mapDepth; ++k) {
            for (i = 0; i < mapHeight; ++i) {
                for (j = 0; j < mapWidth; ++j) {
                    myfile >> p;
                    myfile >> buff;
                    tileMatrix.emplace_back(p - 1);
                }
            }
        }

        myfile.close();

    } else{
        cout << "Unable to open file \"" << file << "\" on TileMap";
        exit(1);
    }
}

void TileMap::SetTileSet(TileSet *tSet) {
    tileSet = tSet;
}

int &TileMap::At(int x, int y, int z) {
    int index = (z*mapWidth*mapHeight) + (y*mapWidth) + x;
    return tileMatrix[index];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    int startIndex = layer*mapWidth*mapDepth;

    for (int i = 0; i < mapDepth*mapDepth; ++i) {
        tileSet->RenderTile();
    }
}

void TileMap::Render() {

}

int TileMap::GetWidth() {
    return 0;
}

int TileMap::GetHeight() {
    return 0;
}

int TileMap::GetDepth() {
    return 0;
}
