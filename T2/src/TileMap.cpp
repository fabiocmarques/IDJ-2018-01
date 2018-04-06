//
// Created by fabio on 28/03/18.
//

#include <Camera.h>
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
                    tileMatrix.emplace_back(--p);
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
    int i, j, index = 0;
    int tWidth = tileSet->GetTileWidth(), tHeight = tileSet->GetTileHeight();


    for (i = 0; i < mapHeight; ++i) {
        for (j = 0; j < mapWidth; ++j) {
            index = At(j, i, layer);
            if(index > -1){
                tileSet->RenderTile(index, (j*tWidth - cameraX), (i*tHeight - cameraY));
            }
        }
    }
}

void TileMap::Render() {

    for (int i = 0; i < mapDepth; ++i) {
        RenderLayer(i, (int)(Camera::pos.x - 0.2*Camera::pos.x*i), (int)(Camera::pos.y - 0.2*Camera::pos.y*i));
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

TileMap::~TileMap() {
    delete tileSet;
}

void TileMap::Update(float dt) {

}

bool TileMap::Is(string type) {
    return type == "TileMap";
}
