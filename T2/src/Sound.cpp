//
// Created by fabio on 18/03/18.
//

#include <Resources.h>
#include "Sound.h"

Sound::Sound(GameObject &associated) : Component(associated), chunk(nullptr) {

}

Sound::Sound(GameObject &associated, string file) : Component(associated), chunk(nullptr) {
    Open(file);
}

void Sound::Play(int times) {
    if(chunk != nullptr){
        Mix_PlayChannel(10, chunk, times-1);
    }
}

void Sound::Stop() {
    Mix_HaltChannel(-1);
}

void Sound::Open(string file) {
    chunk = Resources::GetSound(file);
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
    Stop();
}
