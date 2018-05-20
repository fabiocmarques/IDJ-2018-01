//
// Created by fabio on 17/05/18.
//

#ifndef T2_ENDSTATE_H
#define T2_ENDSTATE_H


#include "State.h"
#include "Music.h"

using namespace std;

class EndState : public State {
    Music backgroundMusic;

public:
    EndState();
    ~EndState();

    void LoadAssets() override; 
    
    void LoadAssets(string path = "");

    void Update(float dt) override;

    void Render() override;

    void Start() override;

    void Pause() override;

    void Resume() override;
};


#endif //T2_ENDSTATE_H
