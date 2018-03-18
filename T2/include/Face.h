//
// Created by fabio on 18/03/18.
//

#ifndef T1_FACE_H
#define T1_FACE_H


#include "Component.h"

class Face : public Component {
    int hitpoints;

public:
    Face(GameObject &associated);
    void Damage(int damage);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;
};


#endif //T1_FACE_H
