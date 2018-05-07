//
// Created by Fabio Marques on 05/05/2018.
//

#include "Collider.h"

void Collider::Update(float dt) {
    float width = associated.box.w*scale.x, height = associated.box.h*scale.y;
    Vec2 objectCenter = associated.box.GetCenter();

    box.w = width;
    box.h = height;
    box.x = (objectCenter.x - width/2) + offset.x*(float)sin(associated.angleDeg*PI/180);
    box.y = (objectCenter.y - height/2) + offset.y*(float)cos(associated.angleDeg*PI/180);;

}

void Collider::Render() {

}

bool Collider::Is(string type) {
    return type == "Collider";
}

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset) {

}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}
