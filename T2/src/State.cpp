//
// Created by fabio on 15/03/18.
//

#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include "TileMap.h"
#include "State.h"

State::State() : started(false) {
    unique_ptr<GameObject> go(new GameObject());
    Sprite* spr = new Sprite(*go, "assets/img/ocean.jpg");

    go->AddComponent(new CameraFollower(*go));
    go->AddComponent(spr);
    go->box.x = 0;
    go->box.y = 0;
    go->box.h = spr->GetHeight();
    go->box.w = spr->GetWidth();

   objectArray.emplace_back(move(go));


    unique_ptr<GameObject> go2(new GameObject());
    TileSet* ts = new TileSet(TILE_WIDTH, TILE_HEIGHT, "assets/img/tileset.png");
    TileMap* map = new TileMap(*go2, "assets/map/tileMap.txt", ts);
    LoadAssets();

    go2->AddComponent(map);
    go2->box.x = 0;
    go2->box.y = 0;

    objectArray.emplace_back(move(go2));


    quitRequested = false;
    music.Play();
}

void State::LoadAssets() {
    music.Open("assets/audio/stageState.ogg");
}

void State::Update(float dt) {
    InputManager IM = InputManager::GetInstance();

    if(IM.IsKeyDown(ESCAPE_KEY) || IM.QuitRequested()){
        quitRequested = true;
    }

    Camera::Update(dt);

    if(IM.KeyPress(SDLK_SPACE)){
        Vec2 objPos = Vec2( 200, 0 ).GetRotated( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2( IM.GetMouseX(), IM.GetMouseY());
        AddObject(objPos.x + Camera::pos.x, objPos.y + Camera::pos.y);
    }

    for (int i = 0; i < (int)objectArray.size(); ++i) {
        objectArray[i]->Update(dt);
    }

    for (int i = 0; i < (int)objectArray.size(); ++i) {
        if(objectArray[i]->IsDead()){
            if(!Mix_Playing(10)){
                objectArray.erase(objectArray.begin() + i);
            }

        }
    }
}

void State::Render() {
    for (int i = 0; i < (int)objectArray.size(); ++i) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

State::~State() {
    objectArray.clear();
}

void State::AddObject(float mouseX, float mouseY) {
    unique_ptr<GameObject> go(new GameObject());
    Sprite *spr = new Sprite((*go), "assets/img/penguinface.png");
    go->AddComponent(spr);
    go->box.x = mouseX;
    go->box.y = mouseY;
    go->box.h = spr->GetHeight();
    go->box.w = spr->GetWidth();

    go->AddComponent(new Sound((*go), "assets/audio/boom.wav"));
    go->AddComponent(new Face((*go)));

   objectArray.emplace_back(move(go));
}

void State::Start() {
    LoadAssets();

    for (int i = 0; i < (int)objectArray.size(); ++i) {
        objectArray[i]->Start();
    }

    started = true;
}

weak_ptr<GameObject> State::AddObject(GameObject *go) {
    shared_ptr<GameObject> sptr(go);

    objectArray.push_back(sptr);
    if(started){
        go->Start();
    }

    return weak_ptr<GameObject>(sptr);
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {

    for (int i = 0; i < (int)objectArray.size(); ++i) {
        if(objectArray[i] == go){
            return weak_ptr<GameObject>(objectArray[i]);
        }
    }

    return weak_ptr<GameObject>();
}
