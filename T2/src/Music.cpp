//
// Created by fabio on 15/03/18.
//

#include <Resources.h>
#include "../include/Music.h"

Music::Music() : music(nullptr) { }

Music::Music(string file) : music(nullptr) {
    Open(file);
}

void Music::Play(int times) {

    if(music != nullptr){
        Mix_PlayMusic(music, times);
    }

}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    music = Resources::GetMusic(file);
}

bool Music::IsOpen() {
    return (music != nullptr);
}

Music::~Music() {
    Stop();
}
