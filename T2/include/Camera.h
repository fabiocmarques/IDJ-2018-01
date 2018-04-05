//
// Created by Fabio Marques on 04/04/2018.
//

#ifndef T2_CAMERA_H
#define T2_CAMERA_H


#include "GameObject.h"
#include "Vec2.h"
#include "InputManager.h"
#include <iostream>

using namespace std;

class Camera {
    static GameObject* focus;

public:
    static Vec2 pos;
    static Vec2 speed;

    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);
};


#endif //T2_CAMERA_H
