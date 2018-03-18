//
// Created by fabio on 18/03/18.
//

#include "Face.h"
#include "Sound.h"

Face::Face(GameObject &associated) : Component(associated), hitpoints(50) {}

void Face::Damage(int damage) {
    hitpoints -= damage;

    if(hitpoints <= 0){
        associated.RemoveComponent(this);
        Sound* c = (Sound*)associated.GetComponent("Sound");
        if(c != nullptr){
            (*c).Play();
        }
    }
}
