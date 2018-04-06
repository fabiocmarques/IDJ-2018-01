//
// Created by Fabio Marques on 06/04/2018.
//

#ifndef T2_ALIEN_H
#define T2_ALIEN_H


#include <queue>
#include <vector>
#include "Component.h"

using namespace std;

class Alien : public Component {
    class Action{
    public:

        enum ActionType{
            MOVE,
            SHOOT
        };

        Action(ActionType type, float x, float y);

        ActionType type;
        Vec2 pos;
    };

    Vec2 speed;
    int hp;

    queue<Action> taskQueue;
    vector<weak_ptr<GameObject>> minionArray;
public:
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;
    void Start() override;

    Alien(GameObject& associated, int nMinions);
    ~Alien();

};



#endif //T2_ALIEN_H
