//
// Created by Fabio Marques on 06/04/2018.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include <Minion.h>
#include <Game.h>
#include "Alien.h"

#define SPEED 50
#define MARGIN 1

void Alien::Update(float dt) {
    InputManager IM = InputManager::GetInstance();
    float finalX;
    float finalY;


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

                if (abs(finalY - associated.box.y) < abs(finalX - associated.box.x)) {
                    speed.x = (associated.box.x < finalX) ? SPEED : -SPEED;
                    speed.y = (finalY - associated.box.y) * (SPEED / abs(finalX - associated.box.x));
                } else {
                    speed.y = (associated.box.y < finalY) ? SPEED : -SPEED;
                    speed.x = (finalX - associated.box.x) * (SPEED / abs(finalY - associated.box.y));

                }

            }

            associated.box.x += (abs(finalX - associated.box.x) < abs(speed.x * dt) ? (finalX -
                                                                                       associated.box.x) :
                                 speed.x * dt);
            associated.box.y += (abs(finalY - associated.box.y) < abs(speed.y * dt) ? (finalY -
                                                                                       associated.box.y) :
                                 speed.y * dt);

            if (((associated.box.x <= finalX + MARGIN) && (associated.box.x >= finalX - MARGIN)) &&
                ((associated.box.y <= finalY + MARGIN) && (associated.box.y >= finalY - MARGIN))) {
                taskQueue.pop();
                speed.x = 0;
                speed.y = 0;
            }


        } else if (taskQueue.front().type == Action::SHOOT) {
            if(!minionArray.empty()){

                shared_ptr<GameObject> obj = minionArray[0].lock();
                Minion* minion = (Minion*)obj.get()->GetComponent("Minion");

                minion->Shoot(Vec2(IM.GetMouseX() + Camera::pos.x, IM.GetMouseY() + Camera::pos.y));

            } else{
                cout << "No minion associated." << endl;
                taskQueue.pop();
            }
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

    if(!minionArray.empty()){

        int angleStep = 360/minionArray.size();
        Minion* minion = nullptr;
        weak_ptr<GameObject> alienPtr = Game::GetInstance().GetState().GetObjectPtr(&associated);

        cout << "4" << endl;

        for (int angle = 0; angle < 360; angle += angleStep) {
            shared_ptr<GameObject> go = shared_ptr<GameObject>(new GameObject());
            go->AddComponent(new Minion(*go, alienPtr, angle));

            Game::GetInstance().GetState().AddObject(go.get());
        }

        cout << "5" << endl;
    }

}

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed(*new Vec2()), hp(100),minionArray(nMinions) {
    Sprite* spr = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(spr);
    associated.box.h = spr->GetHeight();
    associated.box.w = spr->GetWidth();

}

Alien::~Alien() {
    for(auto it = minionArray.begin(); it != minionArray.end(); ){
        if(it->lock() != nullptr){
            (it->lock().get())->RequestDelete();
        }

        it = minionArray.erase(it);
    }

    minionArray.clear();
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) : type(type), pos(x, y) {
}
