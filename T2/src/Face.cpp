//
// Created by fabio on 18/03/18.
//

#include "Face.h"


Face::Face(GameObject &associated) : Component(associated), hitpoints(30) {}

void Face::Damage(int damage) {
    hitpoints -= damage;

    //cout << "Vida: " << hitpoints << endl;

    if(hitpoints <= 0){
        Sound* c = (Sound*)associated.GetComponent("Sound");
        if(c != nullptr) {
            cout << "Start." << endl;
            c->Play();
            cout << "Finish." << endl;
        }
        associated.RequestDelete();
    }
}

bool Face::Is(string type) {
    return type == "Face";
}

void Face::Render() {

}

void Face::Update(float dt) {
}
