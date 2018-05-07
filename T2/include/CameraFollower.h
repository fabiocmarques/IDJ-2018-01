//
// Created by fabio on 05/04/18.
//

#ifndef T2_CAMERAFOLLOWER_H
#define T2_CAMERAFOLLOWER_H


#include "Component.h"
#include "Game.h"

class CameraFollower : public Component {
    bool adjustCenter;

    void AdjustCenter();
public:
    CameraFollower(GameObject& go, bool adjCenter = false);

    void Update(float dt) override;

    void Render() override;

    bool Is(string type) override;


};


#endif //T2_CAMERAFOLLOWER_H
