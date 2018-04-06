//
// Created by fabio on 18/03/18.
//

#ifndef T1_GAMEOBJECT_H
#define T1_GAMEOBJECT_H

#include <vector>
#include "Rect.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

class Component;

class GameObject {
    bool isDead;
    vector<Component*> components;

    bool started;

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

    void Start();

    Rect box;
};






#endif //T1_GAMEOBJECT_H
