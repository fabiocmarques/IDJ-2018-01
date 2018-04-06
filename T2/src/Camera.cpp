//
// Created by Fabio Marques on 04/04/2018.
//

#include "Camera.h"

#define STD_WIDTH 1024
#define STD_HEIGHT 600

#define SPEED 300

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = *new Vec2();
Vec2 Camera::speed = *new Vec2();

void Camera::Follow(GameObject *newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if(focus != nullptr){
        Camera::pos.x = focus->box.x + STD_WIDTH/2;
        Camera::pos.y = focus->box.y + STD_HEIGHT/2;
    } else {
        Camera::speed.x = SPEED;
        Camera::speed.y = SPEED;

        InputManager IM = InputManager::GetInstance();

        if(IM.IsKeyDown(UP_ARROW_KEY)){
            Camera::pos.y -= Camera::speed.y * dt;
        } else if(IM.IsKeyDown(DOWN_ARROW_KEY)){
            Camera::pos.y += Camera::speed.y * dt;
        } else if(IM.IsKeyDown(RIGHT_ARROW_KEY)){
            Camera::pos.x += Camera::speed.x * dt;
        } else if(IM.IsKeyDown(LEFT_ARROW_KEY)){
            Camera::pos.x -= Camera::speed.x * dt;
        }
    }
}
