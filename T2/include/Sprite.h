//
// Created by fabio on 15/03/18.
//

#ifndef T1_SPRITE_H
#define T1_SPRITE_H

#include <string>
#include <iostream>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Component.h"

using namespace std;

class Sprite : public Component{

    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;

public:
    Sprite(GameObject &associated);
    Sprite(GameObject &associated, string file);
    ~Sprite();

    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    int GetWidth();
    int GetHeight();
    bool IsOpen();

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;
};


#endif //T1_SPRITE_H
