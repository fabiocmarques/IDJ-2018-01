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

    associated.box.w = width/frameCount;
    associated.box.h = height;

    SetClip(0, 0, width/frameCount, height);
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
    return (width*scale.x)/frameCount;
}

int Sprite::GetHeight() {
    return height*scale.y;
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}


void Sprite::Update(float dt) {
    timeElapsed += dt;
    if(timeElapsed >= frameTime){
        ++currentFrame;
        if(currentFrame >= frameCount){
            currentFrame = 0;
        }

        timeElapsed = 0;

        SetFrame(currentFrame);
    }
}

bool Sprite::Is(string type) {
    return (type == "Sprite");
}

Sprite::Sprite(GameObject &associated) : Component(associated), texture(nullptr), width(0), height(0), scale(1, 1) {

}


Sprite::Sprite(GameObject &associated, string file, bool center, int frameCount, float frameTime) : Component(associated), texture(nullptr), width(0), height(0), scale(1, 1), centered(center), frameCount(frameCount), frameTime(frameTime), currentFrame(0), timeElapsed(0) {
    Open(file);
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect;
    dstrect.x = (int)( centered ? x - scale.x*clipRect.w/2 : x);
    dstrect.y = (int)( centered ? y - scale.y*clipRect.h/2 : y);
    dstrect.w = (int)(clipRect.w*scale.x);
    dstrect.h = (int)(clipRect.h*scale.y);

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, associated.angleDeg,
                     nullptr , SDL_FLIP_NONE);
}

Vec2 Sprite::GetScale() {
    return scale;
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

void Sprite::SetFrame(int frame) {
    SetClip((width/frameCount)*currentFrame,  0, width/frameCount, height);
}

void Sprite::SetFrameCount(int frameCount) {
    this->frameCount = frameCount;
    currentFrame = 0;

    associated.box.w = width/this->frameCount;
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}


