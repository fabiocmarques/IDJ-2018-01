//
// Created by fabio on 15/03/18.
//

#include "../include/State.h"
#include "../include/Game.h"

State::State() : bg((GameObject &) new GameObject(), "assets/img/ocean.jpg") {
    LoadAssets();
    quitRequested = false;
    music.Play();
}

void State::LoadAssets() {
    music.Open("assets/audio/stageState.ogg");
}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    bg.Render();
}

bool State::QuitRequested() {
    return quitRequested;
}