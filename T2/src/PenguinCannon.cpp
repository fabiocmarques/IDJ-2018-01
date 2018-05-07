//
// Created by fabio on 19/04/18.
//

#include <Sprite.h>
#include <PenguinBody.h>
#include <Game.h>
#include <Bullet.h>
#include <InputManager.h>
#include <Camera.h>
#include <Collider.h>
#include "PenguinCannon.h"

void PenguinCannon::Update(float dt) {
    if(pbody.lock() == nullptr){
        associated.RequestDelete();
        return;
    }

    InputManager IM = InputManager::GetInstance();
    float distX = IM.GetMouseX() + Camera::pos.x, distY = IM.GetMouseY() + Camera::pos.y;
    Vec2 center = associated.box.GetCenter();
    Vec2 target(distX - center.x, distY - center.y);
    angle = target.IncX();
    associated.angleDeg = 90 - (angle * 180 / PI);


    Vec2 bodyCenter = pbody.lock().get()->box.GetCenter();
    associated.box.x = bodyCenter.x - associated.box.w/2;
    associated.box.y = bodyCenter.y - associated.box.h/2;

    if (IM.MousePress(LEFT_MOUSE_BUTTON)) {
        Shoot();
    }

}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(string type) {
    return type == "PenguinCannon";
}

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody) : Component
(associated), angle(0), pbody(penguinBody) {

    Sprite* spr = new Sprite(associated, "assets/img/cubngun.png");

    associated.AddComponent(spr);
    associated.box.h = spr->GetHeight();
    associated.box.w = spr->GetWidth();

    associated.SetCenter();

    //associated.AddComponent(new Collider(associated));
}

void PenguinCannon::Shoot() {
    Vec2 center = associated.box.GetCenter();

    shared_ptr<GameObject> go(new GameObject());
    go->box.x = center.x + (associated.box.w/2)*sin(angle);
    go->box.y = center.y + (associated.box.w/2)*cos(angle);

    go->AddComponent(new Bullet(*go, angle, BULLET_SPEED, 30, 1000, "assets/img/penguinbullet.png", 4, 0.3, false));


    Game::GetInstance().GetState().AddObject(go);
}
