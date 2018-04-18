//
// Created by fabio on 05/04/18.
//

#include <Camera.h>
#include "CameraFollower.h"

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(string type) {
    return type == "CameraFollower";
}

CameraFollower::CameraFollower(GameObject &go) : Component(go) {

}
