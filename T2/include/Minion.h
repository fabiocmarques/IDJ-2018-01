//
// Created by fabio on 11/04/18.
//

#ifndef T2_MINION_H
#define T2_MINION_H


#include "GameObject.h"
#include "Component.h"
#include <cmath>

#define PI 3.14159265
#define BULLET_SPEED 40

using namespace std;

class Minion : public Component {
    GameObject& alienCenter;
    float arc;

public:
    Minion(GameObject& associated, weak_ptr<GameObject> alCenter, float arcOffsetDeg = 0);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void Shoot(Vec2 target);
};


#endif //T2_MINION_H
