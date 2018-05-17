//
// Created by fabio on 16/05/18.
//

#ifndef T2_TITLESTATE_H
#define T2_TITLESTATE_H


#include "State.h"

class TitleState : public State {
    
public:
    TitleState();
    ~TitleState();

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;
};


#endif //T2_TITLESTATE_H
