//
// Created by Fabio Marques on 06/04/2018.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include <Minion.h>
#include <Game.h>
#include "Alien.h"

#define ROT_SPEED 0.15
#define SPEED 100
#define MARGIN 1

void Alien::Update(float dt) {
    InputManager IM = InputManager::GetInstance();
    float finalX;
    float finalY;
    Vec2 center = associated.box.CenterRec();

    associated.angleDeg -= (ROT_SPEED * dt * 180 / PI);
    if (associated.angleDeg <= -360) {
        associated.angleDeg += 360;
    }

    if (IM.MousePress(LEFT_MOUSE_BUTTON)) {
        taskQueue.push(
                *new Action(Action::SHOOT, IM.GetMouseX() + Camera::pos.x, IM.GetMouseY() + Camera::pos.y));
    } else if (IM.MousePress(RIGHT_MOUSE_BUTTON)) {
        taskQueue.push(
                *new Action(Action::MOVE, IM.GetMouseX() + Camera::pos.x, IM.GetMouseY() + Camera::pos.y));
        //cout << "Position to GO: X-" << IM.GetMouseX() + Camera::pos.x << " Y-" << IM.GetMouseY() +
        // Camera::pos.y << endl;
    }

    if (!taskQueue.empty()) {
        if (taskQueue.front().type == Action::MOVE) {
            finalX = taskQueue.front().pos.x;
            finalY = taskQueue.front().pos.y;

            if (speed.Mag() == 0) {

                if (abs(finalY - center.y) < abs(finalX - center.x)) {
                    speed.x = (center.x < finalX) ? SPEED : -SPEED;
                    speed.y = (finalY - center.y) * (SPEED / abs(finalX - center.x));
                } else {
                    speed.y = (center.y < finalY) ? SPEED : -SPEED;
                    speed.x = (finalX - center.x) * (SPEED / abs(finalY - center.y));

                }

            }

            associated.box.x += (abs(finalX - center.x) < abs(speed.x * dt) ? (finalX - center.x) : speed.x *
                                                                                                    dt);

            associated.box.y += (abs(finalY - center.y) < abs(speed.y * dt) ? (finalY - center.y) :
                                 speed.y * dt);

            center = associated.box.CenterRec();

            if (((center.x <= finalX + MARGIN) && (center.x >= finalX - MARGIN)) &&
                ((center.y <= finalY + MARGIN) && (center.y >= finalY - MARGIN))) {
                taskQueue.pop();
                speed.x = 0;
                speed.y = 0;
            }


        } else if (taskQueue.front().type == Action::SHOOT) {
            if (!minionArray.empty()) {
                float distX = IM.GetMouseX() + Camera::pos.x, distY = IM.GetMouseY() + Camera::pos.y;
                Vec2 target(distX, distY);

                shared_ptr<GameObject> closest = nullptr;


                for (auto it = minionArray.begin(); it < minionArray.end(); it++) {
                    shared_ptr<GameObject> obj = it->lock();
                    cout << "inside" << endl;
                    if (obj != nullptr && (closest == nullptr ||
                                           target.Sum(obj->box.CenterRec(), false).Mag() <
                                           target.Sum(closest->box.CenterRec(), false).Mag())) {
                        closest = obj;
                    }

                }

                cout << "2" << endl;

                Minion *minion = (Minion *) closest.get()->GetComponent("Minion");

                minion->Shoot(target);

                cout << "3" << endl;

            } else {
                cout << "No minion associated." << endl;
            }

            taskQueue.pop();
        }
    }

    if (hp <= 0) {
        associated.RequestDelete();
    }
}

void Alien::Render() {

}

bool Alien::Is(string type) {
    return type == "Alien";
}

void Alien::Start() {

    if (!minionArray.empty()) {

        int angleStep = 360 / minionArray.size();
        weak_ptr<GameObject> alienPtr = Game::GetInstance().GetState().GetObjectPtr(&associated);

        for (int angle = 0, i = 0; angle < 360; angle += angleStep, ++i) {
            shared_ptr<GameObject> go = shared_ptr<GameObject>(new GameObject());
            go->AddComponent(new Minion(*go, alienPtr, angle));

            Game::GetInstance().GetState().AddObject(go);

            minionArray[i] = weak_ptr<GameObject>(go);
        }


    }

}

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed(*new Vec2()), hp(100),
                                                     minionArray(nMinions) {
    Sprite *spr = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(spr);
    associated.box.h = spr->GetHeight();
    associated.box.w = spr->GetWidth();

    associated.SetCenter();

    associated.angleDeg = 0;
    //spr->SetScaleX(2, 2);

}

Alien::~Alien() {
    for (auto it = minionArray.begin(); it != minionArray.end();) {
        if (it->lock() != nullptr) {
            (it->lock().get())->RequestDelete();
        }

        it = minionArray.erase(it);
    }

    minionArray.clear();
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) : type(type), pos(x, y) {
}
