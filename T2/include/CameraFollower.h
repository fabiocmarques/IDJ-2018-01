//
// Created by fabio on 05/04/18.
//

#ifndef T2_CAMERAFOLLOWER_H
#define T2_CAMERAFOLLOWER_H


#include "Component.h"

class CameraFollower : public Component {
public:
    CameraFollower(GameObject& go);

    void Update(float dt) override;

    void Render() override;

    bool Is(string type) override;
};


#endif //T2_CAMERAFOLLOWER_H
