//
// Created by Fabio Marques on 06/04/2018.
//

#include <Sprite.h>
#include "Alien.h"

void Alien::Update(float dt) {

}

void Alien::Render() {

}

bool Alien::Is(string type) {
    return false;
}

void Alien::Start() {
    Component::Start();
}

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed(*new Vec2()), hp(100), minionArray(nMinions) {

    associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));

}

Alien::~Alien() {
    for(auto it = minionArray.begin(); it != minionArray.end(); ){
        it = minionArray.erase(it);
    }

    minionArray.clear();
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) {

}
