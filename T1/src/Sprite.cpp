//
// Created by fabio on 15/03/18.
//

#include "../include/Sprite.h"
#include "../include/Game.h"

Sprite::Sprite() : texture(nullptr) { }

Sprite::Sprite(string file) : texture(nullptr) {
    Open(file);
}

Sprite::~Sprite() {
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(string file) {
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if(texture == nullptr){
        cout << "Erro: " << SDL_GetError() << endl;
        cout << "Fail to open the image: " << file << " .";
        exit(1);
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return (texture != nullptr) ? true : false;
}

