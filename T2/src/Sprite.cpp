//
// Created by fabio on 15/03/18.
//

#include <Resources.h>
#include <Camera.h>
#include "../include/Sprite.h"
#include "../include/Game.h"

Sprite::~Sprite() {

}

void Sprite::Open(string file) {
    texture = Resources::GetImage(file);

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
    Render(associated.box.x - (int)Camera::pos.x, associated.box.y - (int)Camera::pos.y);
}

int Sprite::GetWidth() {
    return width*scale.x;
}

int Sprite::GetHeight() {
    return height*scale.y;
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}


void Sprite::Update(float dt) {

}

bool Sprite::Is(string type) {
    return (type == "Sprite");
}

Sprite::Sprite(GameObject &associated) : Component(associated), texture(nullptr), width(0), height(0), scale(1, 1) {

}


Sprite::Sprite(GameObject &associated, string file, bool center) : Component(associated), texture(nullptr), 
width(0), height(0), scale(1, 1), centered(center) {
    Open(file);
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect, center;
    dstrect.x = ( centered ? x - scale.x*width/2 : x);
    dstrect.y = ( centered ? y - scale.y*height/2 : y);
    dstrect.w = clipRect.w*scale.x;
    dstrect.h = clipRect.h*scale.y;

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, associated.angleDeg,
                     nullptr, SDL_FLIP_NONE);
}

Vec2 Sprite::GetScale() {
    return Vec2();
}

void Sprite::SetScaleX(float scaleX, float scaleY) {
    if(scaleX != 0){
        scale.x = scaleX;
        associated.box.x = associated.box.x - clipRect.x*scale.x/2;
    }

    if(scaleY != 0){
        scale.y = scaleY;
        associated.box.y = associated.box.y - clipRect.y*scale.y/2;
    }
}


