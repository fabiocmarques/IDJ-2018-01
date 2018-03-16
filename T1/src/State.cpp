//
// Created by fabio on 15/03/18.
//

#include "../include/State.h"
#include "../include/Game.h"

State::State() : bg("../img/ocean.jpg") {
    quitRequested = false;
}

void State::LoadAssets() {

}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    bg.Render(STD_WIDTH, STD_HEIGHT);
}

bool State::QuitRequested() {
    return quitRequested;
}