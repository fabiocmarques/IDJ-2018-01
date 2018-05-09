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

#include <cmath>

#include <vector>
#include <memory>

using namespace std;


class StageState : public State {

    Music music;
    bool quitRequested;

    void AddObject(float mouseX, float mouseY);

    bool started;
    vector<shared_ptr<GameObject>> objectArray;

public:
    StageState();
    ~StageState();

    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    weak_ptr<GameObject> AddObject(shared_ptr<GameObject> go);
    weak_ptr<GameObject> GetObjectPtr(GameObject* go);
};


#endif //T1_STATE_H
