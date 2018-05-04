//
// Created by fabio on 11/04/18.
//

#include <Sprite.h>
#include <Game.h>
#include "Minion.h"
#include "Bullet.h"

#define CENTER_DIST 150
#define SPEED 0.3

#define PI 3.14159265

void Minion::Update(float dt) {
    Vec2 v = *new Vec2(CENTER_DIST, 0);
    Rect finalPos;

    if(!associated.IsDead()){

        arc += SPEED*dt;
        if(arc >= 2*PI){
            arc -= 2*PI;
        }

        associated.angleDeg += (SPEED*dt*180/PI);
        if(associated.angleDeg >= 360){
            associated.angleDeg -= - 360;
        }


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
    Sprite* spr = new Sprite(associated, "assets/img/minion.png", true);
    float sc = 1 + (rand() % 500 + 1)/1000.0;
    associated.AddComponent(spr);
    associated.box.h = spr->GetHeight()*sc;
    associated.box.w = spr->GetWidth()*sc;

    associated.angleDeg = 90 + arcOffsetDeg;
    
    //cout << sc << endl;

    Vec2 v = *new Vec2(CENTER_DIST, 0);
    v = v.GetRotated(arc);

    Rect finalPos = alienCenter.box.SumVec2(v);

    associated.box.x = finalPos.x;
    associated.box.y = finalPos.y;

    spr->SetScaleX(sc, sc);
}

void Minion::Shoot(Vec2 target) {
    Vec2 vet((target.x)-associated.box.x, (target.y)-associated.box.y);
    float angle = vet.IncX();

    shared_ptr<GameObject> go(new GameObject());
    go->box.x = associated.box.x;
    go->box.y = associated.box.y;

    go->AddComponent(new Bullet(*go, angle, BULLET_SPEED, 10, 500, "assets/img/minionbullet1.png"));


    Game::GetInstance().GetState().AddObject(go);

}
