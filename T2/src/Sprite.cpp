//
// Created by fabio on 15/03/18.
//

#include "../include/Sprite.h"
#include "../include/Game.h"

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

    associated.box.w = width;
    associated.box.h = height;

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render() {
    Render(associated.box.x, associated.box.y);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}


void Sprite::Update(float dt) {

}

bool Sprite::Is(string type) {
    return (type == "Sprite");
}

Sprite::Sprite(GameObject &associated) : Component(associated), texture(nullptr), width(0), height(0) {

}


Sprite::Sprite(GameObject &associated, string file) : Component(associated), texture(nullptr), width(0), height(0) {
    Open(file);
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
}


