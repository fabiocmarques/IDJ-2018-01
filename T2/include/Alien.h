//
// Created by Fabio Marques on 06/04/2018.
//

#ifndef T2_ALIEN_H
#define T2_ALIEN_H


#include <queue>
#include <vector>
#include "Component.h"
#include "Being.h"

#define COOLDOWN 3

using namespace std;

class Alien : public Component, public Being {

    enum AlienState{
        MOVING,
        RESTING
    };

    Vec2 speed;
    int hp;
    vector<weak_ptr<GameObject>> minionArray;

    AlienState state;
    Timer restTimer;
    Vec2 destination;
    
    float timeOffset = 0;

    void Shoot(Vec2 tg);
public:
    static int alienCount;

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;
    void Start() override;

    Alien(GameObject& associated, int nMinions, float offset);
    ~Alien();

    void NotifyCollision(GameObject& other) override;

};



#endif //T2_ALIEN_H
