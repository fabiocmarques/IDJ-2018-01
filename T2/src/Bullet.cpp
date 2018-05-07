//
// Created by fabio on 11/04/18.
//

#include <Sprite.h>
#include <Collider.h>
#include "Bullet.h"

void Bullet::Update(float dt) {

    associated.box.x += speed.x*dt;
    associated.box.y += speed.y*dt;

    distanceLeft -= sqrt((speed.x*dt)*(speed.x*dt) + (speed.y*dt)*(speed.y*dt));

    if(distanceLeft <= 0){
        speed.x = 0;
        speed.y = 0;
        associated.RequestDelete();
    }

}

void Bullet::Render() {

}

bool Bullet::Is(string type) {
    return type == "Bullet";
}

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool targetsPlayer) : Component(associated), distanceLeft(maxDistance), damage(damage), targetsPlayer(targetsPlayer) {

    associated.angleDeg = 90 - angle*180/PI;

    //cout << "Angulo : " << associated.angleDeg << endl;

    Sprite* spr = new Sprite(associated, sprite, frameCount, frameTime);
//    spr->SetFrameCount(frameCount);
//    spr->SetFrame(frameTime);
    associated.AddComponent(spr);
    associated.box.h = spr->GetHeight();
    associated.box.w = spr->GetWidth();
    
    associated.SetCenter();

    this->speed.x = speed*sin(angle);
    this->speed.y = speed*cos(angle);

    associated.AddComponent(new Collider(associated));
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::NotifyCollision(GameObject& other) {
    auto being = other.GetComponent("Being");

    if(being != nullptr){
        associated.RequestDelete();
    }
}
