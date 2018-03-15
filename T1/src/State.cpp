//
// Created by fabio on 15/03/18.
//

#include "../include/State.h"

State::State() : bg() {
    quitRequested = false;
}

void State::LoadAssets() {

}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    bg.Render();
}