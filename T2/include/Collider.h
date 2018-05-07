//
// Created by Fabio Marques on 05/05/2018.
//

#ifndef T2_COLLIDER_H
#define T2_COLLIDER_H

#include "Component.h"

#define PI 3.14159265

class Collider : public Component{
    Vec2 scale;
    Vec2 offset;

public:
    Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0 , 0});

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);

    Rect box;
};

#endif //T2_COLLIDER_H