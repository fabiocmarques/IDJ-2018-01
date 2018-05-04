//
// Created by fabio on 19/04/18.
//

#ifndef T2_PENGUINBODY_H
#define T2_PENGUINBODY_H


#include <Component.h>
#include <iostream>
#include <cmath>

#define PI 3.14159265

using namespace std;

class PenguinBody : public Component {
    weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

public:
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;
    void Start() override;
    
    PenguinBody(GameObject& associated);
    ~PenguinBody();
    
    static PenguinBody* player;   
    
};


#endif //T2_PENGUINBODY_H
