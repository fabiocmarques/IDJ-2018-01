//
// Created by fabio on 15/03/18.
//

#ifndef T1_MUSIC_H
#define T1_MUSIC_H

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>

using namespace std;


class Music {
    Mix_Music* music;

public:
    Music();
    Music(string file);
    ~Music();
    void Play( int times = -1);
    void Stop(int msToStop = 1500);
    void Open(string file);
    bool IsOpen();
};


#endif //T1_MUSIC_H
