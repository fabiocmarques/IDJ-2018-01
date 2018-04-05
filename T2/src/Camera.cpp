//
// Created by Fabio Marques on 04/04/2018.
//

#include "Camera.h"

#define STD_WIDTH 1024
#define STD_HEIGHT 600

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
        Camera::speed.x = STD_WIDTH/(dt < 5 ? 5 : dt);
        Camera::speed.y = STD_HEIGHT/(dt < 5 ? 5 : dt);

        InputManager IM = InputManager::GetInstance();

        if(IM.KeyPress(UP_ARROW_KEY)){
//            cout << "DT: " << dt << endl;
//            cout << "Teste antes de Pos. X: " << Camera::pos.x << " Y: " << Camera::pos.y << endl;
//            cout << "Teste antes de Speed. X: " << Camera::speed.x << " Y: " << Camera::speed.y << endl;
            Camera::pos.y -= Camera::speed.y;
//            cout << "Teste de Pos. X: " << Camera::pos.x << " Y: " << Camera::pos.y << endl;
//            cout << "Teste de Speed. X: " << Camera::speed.x << " Y: " << Camera::speed.y << endl;
        } else if(IM.KeyPress(DOWN_ARROW_KEY)){
            Camera::pos.y += Camera::speed.y;
        } else if(IM.KeyPress(RIGHT_ARROW_KEY)){
            Camera::pos.x += Camera::speed.x;
        } else if(IM.KeyPress(LEFT_ARROW_KEY)){
            Camera::pos.x -= Camera::speed.x;
        }
    }
}
