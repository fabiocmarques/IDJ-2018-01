//
// Created by Fabio Marques on 08/05/2018.
//

#include "State.h"

State::State() : started(false), quitRequested(false), popRequested(false) {

}

void State::LoadAssets() {

}

void State::Update(float dt) {

}

void State::Render() {
    RenderArray();
}

bool State::QuitRequested() {
    return quitRequested;
}

State::~State() {
    objectArray.clear();
}

void State::AddObject(float mouseX, float mouseY) {

}

void State::Start() {
    LoadAssets();

    for (int i = 0; i < (int) objectArray.size(); ++i) {
        objectArray[i]->Start();
    }

    started = true;
}

weak_ptr<GameObject> State::AddObject(GameObject* go) {
    shared_ptr<GameObject> ptr = shared_ptr<GameObject>(go);
    objectArray.push_back(shared_ptr<GameObject>(ptr));
    if (started) {
        ptr->Start();
    }

    return weak_ptr<GameObject>(ptr);
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {

    for (int i = 0; i < (int) objectArray.size(); ++i) {
        if (objectArray[i].get() == go) {
            return weak_ptr<GameObject>(objectArray[i]);
        }
    }

    return weak_ptr<GameObject>();
}

void State::StartArray() {
    LoadAssets();

    for (int i = 0; i < (int) objectArray.size(); ++i) {
        objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt) {
    for (int i = 0; i < (int) objectArray.size(); ++i) {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray() {
    for (int i = 0; i < (int) objectArray.size(); ++i) {
        objectArray[i]->Render();
    }
}

bool State::PopRequested() {
    return popRequested;
}
