//
// Created by fabio on 18/03/18.
//

#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() : isDead(false), started(false), angleDeg(0) {

}

GameObject::~GameObject() {
    int i = components.size() - 1;

    for( ; i >= 0; --i){
        delete components[i];
    }

    components.clear();
}

void GameObject::Update(float dt) {
    for (int i = 0; i < (int)components.size() ; ++i) {
        (*components[i]).Update(dt);
    }
}

void GameObject::Render() {
    for (int i = 0; i < (int)components.size() ; ++i) {
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
    components.emplace_back(cpt);
    if(started){
        cpt->Start();
    }

}

void GameObject::RemoveComponent(Component *cpt) {
    if(!components.empty()){
        int i = 0;
        for( ; i < (int)components.size(); ++i){
            if(components[i] == cpt){
                cout << "Removing obj." << endl;
                components.erase(components.begin() + i);
                break;
            }
        }
    }
}

Component* GameObject::GetComponent(string type) {
    if(!components.empty()){
        int i = 0;
        for( ; i < (int)components.size(); ++i) {
            if ((*components[i]).Is(type) ) {
                return components[i];
            }
        }
    }

    return nullptr;
}

void GameObject::Start() {
    for (int i = 0; i < (int)components.size() ; ++i) {
        (*components[i]).Start();
    }
    started = true;
}
