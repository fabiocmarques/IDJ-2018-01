//
// Created by fabio on 11/04/18.
//

#ifndef T2_BULLET_H
#define T2_BULLET_H

#define PI 3.14159265


#include <Component.h>
#include <cmath>
#include "Being.h"

class Bullet : public Component {
    Vec2 speed;
    float distanceLeft;
    int damage;

public:
    bool targetsPlayer;

    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool targetsPlayer);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    int GetDamage();

    void NotifyCollision(GameObject& other) override;

};


#endif //T2_BULLET_H
