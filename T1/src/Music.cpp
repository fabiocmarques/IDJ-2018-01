//
// Created by fabio on 15/03/18.
//

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
    music = Mix_LoadMUS(file.c_str());
    if(music == nullptr){
        cout << "Error: " << SDL_GetError() << endl;
        cout << "Fail to open the image: '" << file.c_str() << "'.";
        exit(1);
    }
}

bool Music::IsOpen() {
    return (music != nullptr);
}

Music::~Music() {
    Stop();
    Mix_FreeMusic(music);
}
