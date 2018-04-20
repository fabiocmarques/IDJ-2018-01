//
// Created by fabio on 19/04/18.
//

#include <Sprite.h>
#include "PenguinCannon.h"

void PenguinCannon::Update(float dt) {

}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(string type) {
    return false;
}

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody) : Component
(associated), angle(0), pbody(penguinBody) {

    Sprite* spr = new Sprite(associated, "assets/img/cubngun.png");

    associated.AddComponent(spr);
    associated.box.h = spr->GetHeight();
    associated.box.w = spr->GetWidth();

    associated.SetCenter();
}

void PenguinCannon::Shoot() {

}
