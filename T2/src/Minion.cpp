//
// Created by fabio on 11/04/18.
//

#include <Sprite.h>
#include <Game.h>
#include "Minion.h"
#include "Bullet.h"

#define CENTER_DIST 200
#define SPEED 0.5

void Minion::Update(float dt) {
    Vec2 v = *new Vec2(CENTER_DIST, 0);
    Rect finalPos;

    if(!associated.IsDead()){

        arc += SPEED*dt;

        v = v.GetRotated(arc);

        finalPos = alienCenter.box.SumVec2(v);

        associated.box.x = finalPos.x;
        associated.box.y = finalPos.y;

    } else{
        associated.RequestDelete();
    }
}

void Minion::Render() {

}

bool Minion::Is(string type) {
    return type == "Minion";
}

Minion::Minion(GameObject &associated,
               weak_ptr<GameObject> alCenter,
               float arcOffsetDeg) : Component(associated),
                                     alienCenter(*(alCenter.lock().get())),
                                     arc(arcOffsetDeg*PI/180)
{
    Sprite* spr = new Sprite(associated, "assets/img/minion.png");
    associated.AddComponent(spr);
    associated.box.h = spr->GetHeight();
    associated.box.w = spr->GetWidth();

    Vec2 v = *new Vec2(CENTER_DIST, 0);
    v = v.GetRotated(arc);

    Rect finalPos = alienCenter.box.SumVec2(v);

    associated.box.x = finalPos.x;
    associated.box.y = finalPos.y;
}

void Minion::Shoot(Vec2 target) {
    float angle = target.IncX();

    shared_ptr<GameObject> go(new GameObject());

    go->AddComponent(new Bullet(*go, angle, BULLET_SPEED, 10, 500, "assets/img/minionbullet1.jpg"));
    go->box.x = associated.box.x;
    go->box.y = associated.box.y;

    Game::GetInstance().GetState().AddObject(go);

}
