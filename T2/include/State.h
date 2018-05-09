//
// Created by Fabio Marques on 08/05/2018.
//

#ifndef T2_STATE_H
#define T2_STATE_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include <vector>
#include <memory>
#include "GameObject.h"
#include <InputManager.h>
#include <Collision.h>
#include "Collider.h"
#include "Camera.h"

using namespace std;


class State {

protected:
    bool quitRequested;
    bool started;
    bool popRequested;
    vector<shared_ptr<GameObject>> objectArray;

    void StartArray();
    virtual void UpdateArray(float dt);
    virtual void RenderArray();

    void AddObject(float mouseX, float mouseY);
public:
    State();
    virtual ~State();

    virtual void LoadAssets() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual weak_ptr<GameObject> AddObject(GameObject* go);
    virtual weak_ptr<GameObject> GetObjectPtr(GameObject* go);

    bool PopRequested();
    bool QuitRequested();
};


#endif //T2_STATE_H
