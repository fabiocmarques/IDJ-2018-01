//
// Created by Fabio Marques on 06/04/2018.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include <Minion.h>
#include <Game.h>
#include <Collider.h>
#include <Bullet.h>
#include <PenguinBody.h>
#include <Sound.h>
#include "Alien.h"

#define ROT_SPEED 0.15
#define SPEED 100
#define MARGIN 1

int Alien::alienCount = 0;

void Alien::Update(float dt) {
    InputManager IM = InputManager::GetInstance();
    Vec2 center = associated.box.GetCenter();

    associated.angleDeg -= (ROT_SPEED * dt * 180 / PI);
    if (associated.angleDeg <= -360) {
        associated.angleDeg += 360;
    }

    if(PenguinBody::player != nullptr){
        if (state == RESTING) {
            restTimer.Update(dt);

            if (restTimer.Get() >= COOLDOWN) {
                destination = PenguinBody::player->GetPosition();

                if (speed.Mag() == 0) {

                    if (abs(destination.y - center.y) < abs(destination.x - center.x)) {
                        speed.x = (center.x < destination.x) ? SPEED : -SPEED;
                        speed.y = (destination.y - center.y) * (SPEED / abs(destination.x - center.x));
                    } else {
                        speed.y = (center.y < destination.y) ? SPEED : -SPEED;
                        speed.x = (destination.x - center.x) * (SPEED / abs(destination.y - center.y));

                    }

                }

                state = MOVING;
            }
        } else if (state == MOVING) {

            if (((center.x <= destination.x + MARGIN) && (center.x >= destination.x - MARGIN)) &&
                ((center.y <= destination.y + MARGIN) && (center.y >= destination.y - MARGIN))) {
                speed.x = 0;
                speed.y = 0;

                Vec2 target = PenguinBody::player->GetPosition();
                Shoot(target);

                restTimer.Restart();
                state = RESTING;

            } else{
                associated.box.x += (abs(destination.x - center.x) < abs(speed.x * dt) ?
                                     (destination.x - center.x) :
                                     speed.x * dt);

                associated.box.y += (abs(destination.y - center.y) < abs(speed.y * dt) ?
                                     (destination.y - center.y) :
                                     speed.y * dt);
            }


        } else {
            cout << "Unexpected Alien state: " << state << endl;
            exit(1);
        }
    }

    if (hp <= 0) {
        associated.RequestDelete();
    }
}

void Alien::Render() {

}

bool Alien::Is(string type) {
    return (type == "Alien" || Being::Is(type));
}

void Alien::Start() {

    if (!minionArray.empty()) {

        int angleStep = 360 / minionArray.size();
        weak_ptr<GameObject> alienPtr = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);

        for (int angle = 0, i = 0; angle < 360; angle += angleStep, ++i) {
            GameObject* go = new GameObject();
            go->AddComponent(new Minion(*go, alienPtr, angle));

            Game::GetInstance().GetCurrentState().AddObject(go);
            
            minionArray[i] =  Game::GetInstance().GetCurrentState().GetObjectPtr(go);
        }


    }

}

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed(*new Vec2()), hp(100),
                                                     minionArray(nMinions), state(RESTING), restTimer(*new Timer()),
                                                     destination({0, 0}) {

    ++(Alien::alienCount);

    Sprite *spr = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(spr);
    associated.box.h = spr->GetHeight();
    associated.box.w = spr->GetWidth();

    associated.SetCenter();

    associated.angleDeg = 0;

    associated.AddComponent(new Collider(associated));
    //spr->SetScaleX(2, 2);

}

Alien::~Alien() {
    //cout << "Alien sumindo." << endl;
    for (auto it = minionArray.begin(); it != minionArray.end();) {
        if (it->lock() != nullptr) {
            (it->lock().get())->RequestDelete();
        }

        it = minionArray.erase(it);
    }

    minionArray.clear();
    //cout << "Alien sumiu." << endl;
    --(Alien::alienCount);
}

void Alien::NotifyCollision(GameObject &other) {
    auto bullet = (Bullet *) other.GetComponent("Bullet");

    if (bullet != nullptr && !bullet->targetsPlayer) {
        hp -= bullet->GetDamage();

        if (hp <= 0) {
            Vec2 center = associated.box.GetCenter();
            GameObject* go = new GameObject();

            Sprite *spr = new Sprite(*go, "assets/img/aliendeath.png", 4, 0.4, 1.6);
            go->box.x = center.x;
            go->box.y = center.y;
            go->SetCenter();
            go->AddComponent(spr);

            Sound* boom = new Sound(*go, "assets/audio/boom.wav");
            go->AddComponent(boom);
            boom->Play(1);

            //cout << "Shoot" << endl;
            Game::GetInstance().GetCurrentState().AddObject(go);

            associated.RequestDelete();
        }
    }
}

void Alien::Shoot(Vec2 tg) {
    if (!minionArray.empty()) {
        float distX = tg.x, distY = tg.y;
        Vec2 target(distX, distY);

        shared_ptr<GameObject> closest = nullptr;


        for (auto it = minionArray.begin(); it < minionArray.end(); it++) {
            shared_ptr<GameObject> obj = it->lock();
            //cout << "inside" << endl;
            if (obj != nullptr && (closest == nullptr ||
                                   target.Sum(obj->box.GetCenter(), false).Mag() <
                                   target.Sum(closest->box.GetCenter(), false).Mag())) {
                closest = obj;
            }

        }

        Minion *minion = (Minion *) closest.get()->GetComponent("Minion");

        minion->Shoot(target);


    } else {
        cout << "No minion associated." << endl;
    }
}


