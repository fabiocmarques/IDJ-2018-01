//
// Created by fabio on 11/04/18.
//

#ifndef T2_BULLET_H
#define T2_BULLET_H

#define PI 3.14159265


#include <Component.h>
#include <cmath>

class Bullet : public Component {
    Vec2 speed;
    float distanceLeft;
    int damage;

public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    int GetDamage();

};


#endif //T2_BULLET_H
