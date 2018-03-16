//
// Created by fabio on 15/03/18.
//

#ifndef T1_SPRITE_H
#define T1_SPRITE_H

#include <string>

#define INCLUDE_SDL
#include "SDL_include.h"

using namespace std;

class Sprite {

    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;

public:
    Sprite();
    Sprite(string file);
    ~Sprite();

    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
};


#endif //T1_SPRITE_H
