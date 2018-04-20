//
// Created by fabio on 19/04/18.
//

#include <Sprite.h>
#include <PenguinCannon.h>
#include <InputManager.h>
#include <Game.h>
#include "PenguinBody.h"

#define MAX_SPEED 200
#define SPEED_STEP 1
#define STOP_ACC SPEED_STEP*5

PenguinBody* PenguinBody::player = nullptr;

void PenguinBody::Update(float dt) {
    InputManager IM = InputManager::GetInstance();
    
//    if(IM.IsKeyDown('w') || IM.IsKeyDown('W')){
//
//        if(linearSpeed < MAX_SPEED){
//            linearSpeed += (linearSpeed + SPEED_STEP*dt > MAX_SPEED ? MAX_SPEED - linearSpeed : SPEED_STEP*dt);
//        }
//        
////        if(speed.x < MAX_SPEED){
////            speed.x += (speed.x + SPEED_STEP*dt > MAX_SPEED ? MAX_SPEED - speed.x : SPEED_STEP*dt);
////        }
////
////        if(speed.y < MAX_SPEED){
////            speed.y += (speed.y + SPEED_STEP*dt > MAX_SPEED ? MAX_SPEED - speed.y : SPEED_STEP*dt);
////        }        
//        
//    } else if(IM.IsKeyDown('s') || IM.IsKeyDown('S')){
//
//        if(linearSpeed > -MAX_SPEED){
//            linearSpeed -= (linearSpeed - SPEED_STEP*dt < -MAX_SPEED ? MAX_SPEED + linearSpeed : 
//            SPEED_STEP*dt);
//        }
//        
////        if(speed.x > -MAX_SPEED){
////            speed.x -= (speed.x - SPEED_STEP*dt < -MAX_SPEED ? MAX_SPEED + speed.x : SPEED_STEP*dt);
////        }
////
////        if(speed.y > -MAX_SPEED){
////            speed.y -= (speed.y - SPEED_STEP*dt < -MAX_SPEED ? MAX_SPEED + speed.y : SPEED_STEP*dt);
////        }
//    } else{
//        if(linearSpeed > 0){
//            linearSpeed -= (linearSpeed - STOP_ACC*dt < 0 ? linearSpeed : STOP_ACC*dt);
//        } else{
//            linearSpeed += (linearSpeed + STOP_ACC*dt > 0 ? -linearSpeed : STOP_ACC*dt);
//        }
//    }
//
//    if(IM.IsKeyDown('a') || IM.IsKeyDown('A')){
//    
//    } else if(IM.IsKeyDown('d') || IM.IsKeyDown('D')){
//    
//    }
    
    
    
}

void PenguinBody::Render() {

}

bool PenguinBody::Is(string type) {
    return type == "PenguinBody";
}

void PenguinBody::Start() {
    shared_ptr<GameObject> go(new GameObject());
    Vec2 center = associated.box.CenterRec();
    weak_ptr<GameObject> body = Game::GetInstance().GetState().GetObjectPtr(&associated);
    
    go->box.x = center.x;
    go->box.y = center.y;
    go->AddComponent(new PenguinCannon(*go, body));

    Game::GetInstance().GetState().AddObject(go);
    
    pcannon = Game::GetInstance().GetState().GetObjectPtr(go.get());        
}

PenguinBody::PenguinBody(GameObject &associated) : Component(associated), speed(0, 0), linearSpeed
(0), angle(0), hp(0) {

    //pcannon = weak_ptr<GameObject>();
    
    Sprite* spr = new Sprite(associated, "assets/img/penguin.png");

    associated.AddComponent(spr);
    associated.box.h = spr->GetHeight();
    associated.box.w = spr->GetWidth();

    associated.SetCenter();
    
    PenguinBody::player = this;
}

PenguinBody::~PenguinBody() {
    PenguinBody::player = nullptr;
}
