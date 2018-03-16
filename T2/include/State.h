//
// Created by fabio on 15/03/18.
//

#ifndef T1_STATE_H
#define T1_STATE_H

#include "Sprite.h"
#include "Music.h"

#define INCLUDE_SDL
#include "SDL_include.h"


class State {

    Sprite bg;
    Music music;
    bool quitRequested;

public:
    State();

    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
};


#endif //T1_STATE_H
