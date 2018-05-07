//
// Created by fabio on 11/04/18.
//

#include <Sprite.h>
#include <Game.h>
#include <Collider.h>
#include "Minion.h"
#include "Bullet.h"

#define CENTER_DIST 200
#define SPEED 0.3

#define PI 3.14159265

void Minion::Update(float dt) {
    Vec2 v = *new Vec2(CENTER_DIST, 0);
    Vec2 finalPos;

    if(!associated.IsDead()){
        associated.box.x = 0;
        associated.box.y = 0;
        
        associated.SetCenter();
        
        arc += SPEED*dt;
        if(arc >= 2*PI){
            arc -= 2*PI;
        }

        associated.angleDeg += (SPEED*dt*180/PI);
        if(associated.angleDeg >= 360){
            associated.angleDeg -= - 360;
        }


        v = v.GetRotated(arc);

        finalPos = alienCenter.box.GetCenter().Sum(v, true);

        associated.box.x += finalPos.x;
        associated.box.y += finalPos.y;

    } else{
        associated.RequestDelete();
    }
}

void Minion::Render() {

}

bool Minion::Is(string type) {
    return (type == "Minion" || Being::Is(type));
}

Minion::Minion(GameObject &associated,
               weak_ptr<GameObject> alCenter,
               float arcOffsetDeg) : Component(associated),
                                     alienCenter(*(alCenter.lock().get())),
                                     arc(arcOffsetDeg*PI/180)
{
    Sprite* spr = new Sprite(associated, "assets/img/minion.png", true);
    float sc = 1 + (rand() % 500 + 1)/1000.0;
    associated.AddComponent(spr);
    associated.box.h = spr->GetHeight()*sc;
    associated.box.w = spr->GetWidth()*sc;

    spr->SetScaleX(sc, sc);

    associated.angleDeg = 90 + arcOffsetDeg;

    Vec2 v = Vec2(CENTER_DIST, 0);
    v = v.GetRotated(arc);

    Vec2 finalPos = alienCenter.box.GetCenter().Sum(v, true);

    associated.box.x = finalPos.x;
    associated.box.y = finalPos.y;

    associated.SetCenter();

    associated.AddComponent(new Collider(associated));
}

void Minion::Shoot(Vec2 target) {
    Vec2 center = associated.box.GetCenter();
    Vec2 vet((target.x)-center.x, (target.y)-center.y);
    float angle = vet.IncX();

    shared_ptr<GameObject> go(new GameObject());
    go->box.x = center.x;
    go->box.y = center.y;

    go->AddComponent(new Bullet(*go, angle, BULLET_SPEED, 10, 500, "assets/img/minionbullet2.png", 3, 1, true));


    Game::GetInstance().GetState().AddObject(go);

}

void Minion::NotifyCollision(GameObject &other) {
//    auto bullet = (Bullet*)other.GetComponent("Bullet");
//
//    if(bullet != nullptr && !bullet->targetsPlayer){
//        hp -= bullet->GetDamage();
//    }
}
