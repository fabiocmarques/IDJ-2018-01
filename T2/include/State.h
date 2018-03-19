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
#include "Face.h"
#include "Sound.h"

#include <cmath>

#include <vector>
#include <memory>

using namespace std;


class State {

    Music music;
    bool quitRequested;
    vector<unique_ptr<GameObject>> objectArray;

    void Input();
    void AddObject(int mouseX, int mouseY);

public:
    State();
    ~State();

    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
};


#endif //T1_STATE_H
