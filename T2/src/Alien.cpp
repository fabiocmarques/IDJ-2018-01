//
// Created by Fabio Marques on 06/04/2018.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include "Alien.h"

#define SPEED_X 300
#define SPEED_Y 300

void Alien::Update(float dt) {
    InputManager IM = InputManager::GetInstance();

    if (IM.MousePress(LEFT_MOUSE_BUTTON)) {
        taskQueue.push(*new Action(Action::SHOOT, IM.GetMouseX() + Camera::pos.x, IM.GetMouseY() + Camera::pos.y));
    } else if (IM.MousePress(RIGHT_MOUSE_BUTTON)) {
        taskQueue.push(*new Action(Action::MOVE, IM.GetMouseX() + Camera::pos.x, IM.GetMouseY() + Camera::pos.y));
    }

    if(!taskQueue.empty()){
        if(taskQueue.front().type == Action::MOVE){
            Vec2 v(associated.box.x, associated.box.y);

            v = v.Sum(taskQueue.front().pos, false);




            associated.box.x += (abs(v.x) < SPEED_X*dt ? v.x : (v.x/abs(v.x))*SPEED_X*dt);
            associated.box.y += (abs(v.y) < SPEED_Y*dt ? v.y : (v.y/abs(v.y))*SPEED_Y*dt);

            if(associated.box.x == taskQueue.front().pos.x && associated.box.y == taskQueue.front().pos.y)
                taskQueue.pop();

        } else if(taskQueue.front().type == Action::SHOOT){

        }
    }
}

void Alien::Render() {

}

bool Alien::Is(string type) {
    return false;
}

void Alien::Start() {
    Component::Start();
}

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed(*new Vec2()), hp(100),
                                                     minionArray(nMinions) {

    associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));

}

Alien::~Alien() {
//    for(auto it = minionArray.begin(); it != minionArray.end(); ){
//        it = minionArray.erase(it);
//    }

    minionArray.clear();
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) : type(type), pos(x, y) {
}
