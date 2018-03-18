//
// Created by fabio on 18/03/18.
//

#include "GameObject.h"

GameObject::GameObject() : isDead(false) {

}

GameObject::~GameObject() {
    int i = components.size() - 1;

    for( ; i >= 0; --i){
        delete components[i];
    }

    components.clear();
}

void GameObject::Update(float dt) {
    for (int i = 0; i < components.size() ; ++i) {
        (*components[i]).Update(dt);
    }
}

void GameObject::Render() {
    for (int i = 0; i < components.size() ; ++i) {
        (*components[i]).Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component *cpt) {
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt) {
    if(!components.empty()){
        int i = 0;
        for( ; i < components.size(); ++i){
            if(components[i] == cpt){
                components.erase(components.begin() + i);
            }
        }
    }
}

Component *GameObject::GetComponent(string type) {
    if(!components.empty()){
        int i = 0;
        for( ; i < components.size(); ++i) {
            if ((*components[i]).Is(type) ) {
                return components[i];
            }
        }
    }

    return nullptr;
}
