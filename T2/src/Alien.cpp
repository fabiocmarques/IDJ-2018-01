//
// Created by Fabio Marques on 06/04/2018.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include "Alien.h"

#define SPEED 50
#define MARGIN 1

void Alien::Update(float dt) {
    InputManager IM = InputManager::GetInstance();
    float finalX;
    float finalY;


    if (IM.MousePress(LEFT_MOUSE_BUTTON)) {
        taskQueue.push(*new Action(Action::SHOOT, IM.GetMouseX() + Camera::pos.x, IM.GetMouseY() + Camera::pos.y));
    } else if (IM.MousePress(RIGHT_MOUSE_BUTTON)) {
        taskQueue.push(*new Action(Action::MOVE, IM.GetMouseX() + Camera::pos.x, IM.GetMouseY() + Camera::pos.y));
        cout << "Position to GO: X-" << IM.GetMouseX() + Camera::pos.x << " Y-" << IM.GetMouseY() +
                                                                                   Camera::pos.y << endl;
    }

    if(!taskQueue.empty()){
        if(taskQueue.front().type == Action::MOVE){
            finalX = taskQueue.front().pos.x;
            finalY = taskQueue.front().pos.y;

            if(speed.Mag() == 0){

                if(abs(finalY - associated.box.y) < abs(finalX - associated.box.x)){
                    speed.x = (associated.box.x < finalX) ? SPEED : -SPEED;
                    speed.y = (finalY - associated.box.y)*(SPEED/abs(finalX - associated.box.x));
                } else{
                    speed.y = (associated.box.y < finalY) ? SPEED : -SPEED;
                    speed.x = (finalX - associated.box.x)*(SPEED/abs(finalY - associated.box.y));

                }

            }

            associated.box.x += (abs(finalX-associated.box.x) < abs(speed.x*dt) ? (finalX-associated.box.x) : speed.x*dt);
            associated.box.y += (abs(finalY-associated.box.y) < abs(speed.y*dt) ? (finalY-associated.box.y) : speed.y*dt);

            if(((associated.box.x <= finalX + MARGIN) && (associated.box.x >= finalX - MARGIN)) && ((associated.box.y <= finalY + MARGIN) && (associated.box.y >= finalY - MARGIN))){
                taskQueue.pop();
                speed.x = 0;
                speed.y = 0;
            }


        } else if(taskQueue.front().type == Action::SHOOT){
            taskQueue.pop();
        }
    }

    if(hp <= 0 ){
        associated.RequestDelete();
    }
}

void Alien::Render() {

}

bool Alien::Is(string type) {
    return type == "Alien";
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
