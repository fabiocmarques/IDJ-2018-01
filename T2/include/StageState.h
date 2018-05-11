//
// Created by fabio on 15/03/18.
//

#ifndef T1_STATE_H
#define T1_STATE_H

#include "Sprite.h"
#include "Music.h"

#define INCLUDE_SDL
#include "SDL_include.h"
#include "GameObject.h"
#include "Sound.h"
#include "State.h"
#include "TileSet.h"

#include <cmath>

#include <vector>
#include <memory>

using namespace std;


class StageState : public State {

    Music backgroundMusic;
    TileSet* tileSet;

public:
    StageState();
    ~StageState();
    
    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};


#endif //T1_STATE_H
