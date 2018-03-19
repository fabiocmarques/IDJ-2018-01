//
// Created by fabio on 18/03/18.
//

#include "Sound.h"

Sound::Sound(GameObject &associated) : Component(associated), chunk(nullptr) {

}

Sound::Sound(GameObject &associated, string file) : Component(associated), chunk(nullptr) {
    Open(file);
}

void Sound::Play(int times) {
    if(chunk != nullptr){
        Mix_PlayChannel(-1, chunk, times);
    }
}

void Sound::Stop() {
    Mix_HaltChannel(channel);
}

void Sound::Open(string file) {
    chunk = Mix_LoadWAV(file.c_str());
    if(chunk == nullptr){
        cout << "Error: " << SDL_GetError() << endl;
        cout << "Fail to open the sound: '" << file.c_str() << "'.";
        exit(1);
    }
}

bool Sound::IsOpen() {
    return (chunk != nullptr);
}

void Sound::Update(float dt) {

}

void Sound::Render() {

}

bool Sound::Is(string type) {
    return (type == "Sound");
}

Sound::~Sound() {
    if(chunk != nullptr){
        Stop();
        Mix_FreeChunk(chunk);
    }
}
