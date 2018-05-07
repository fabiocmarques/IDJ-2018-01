//
// Created by fabio on 19/04/18.
//

#ifndef T2_PENGUINCANNON_H
#define T2_PENGUINCANNON_H

#include <iostream>
#include <memory>
#include "Component.h"

#define BULLET_SPEED 200

using namespace std;

class PenguinCannon : public Component {
    weak_ptr<GameObject> pbody;
    float angle;

public:
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody);
    
    void Shoot();
    
    
};


#endif //T2_PENGUINCANNON_H
