//
// Created by fabio on 18/03/18.
//

#ifndef T1_SOUND_H
#define T1_SOUND_H

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <string>
#include <iostream>

using namespace std;


#include "Component.h"

class Sound : public Component {
    Mix_Chunk* chunk;
    int channel;

public:
    Sound(GameObject &associated);
    Sound(GameObject &associated, string file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(string file);
    bool IsOpen();

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;




};


#endif //T1_SOUND_H
