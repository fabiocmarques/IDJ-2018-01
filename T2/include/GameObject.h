//
// Created by fabio on 18/03/18.
//

#ifndef T1_GAMEOBJECT_H
#define T1_GAMEOBJECT_H

#include <vector>
#include "Component.h"
#include "Rect.h"
#include <algorithm>

using namespace std;

class GameObject {
    bool isDead;
    vector<Component*> components;

public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(string type);

    Rect box;

};


#endif //T1_GAMEOBJECT_H
