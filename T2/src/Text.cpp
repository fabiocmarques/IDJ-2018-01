//
// Created by Fabio Marques on 16/05/2018.
//

#include <Game.h>
#include <Resources.h>
#include <Timer.h>
#include "Text.h"

#define OFFSET 100
#define COOLDOWN 0.005


void Text::Update(float dt) {
    timer.Update(dt);
    if(timer.Get() >= COOLDOWN){
        if (on) {
            alpha -= 5;
            if (alpha == 0) {
                on = false;
            }
        } else {
            alpha += 5;
            if (alpha == 255) {
                on = true;
            }
        }
        
        //cout << "Alpha: " << (int)alpha << endl;

        if(texture != nullptr){
            SDL_SetTextureAlphaMod(texture, alpha);
        }
        timer.Restart();
    }    
    
}

void Text::Render() {
    SDL_Rect srcR;
    srcR.x = 0;
    srcR.y = 0;
    srcR.w = (int) associated.box.w;
    srcR.h = (int) associated.box.h;

    SDL_Rect dstR;
    dstR.x = (int) ((STD_WIDTH/2) - (associated.box.w / 2)) + OffsetX;
    dstR.y = (int) ((STD_HEIGHT/2) - (associated.box.h / 2)) + OffsetY;
    dstR.w = (int) associated.box.w;
    dstR.h = (int) associated.box.h;

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &srcR, &dstR, associated.angleDeg,
                     nullptr, SDL_FLIP_NONE);
}

bool Text::Is(string type) {
    return type == "Text";
}

void Text::RemakeTexture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    font = Resources::GetFont(fontFile, fontSize);
    if (font == nullptr) {
        cout << "Cannot load font." << endl;
        exit(1);
    }

    SDL_Surface *surface = nullptr;

    color.a = alpha;

    switch (style) {
        case SOLID:
            surface = TTF_RenderText_Solid(font, text.c_str(), color);
            break;

        case SHADED:
            surface = TTF_RenderText_Shaded(font, text.c_str(), color, {0, 0, 0, 0});
            break;

        case BLENDED:
            surface = TTF_RenderText_Blended(font, text.c_str(), color);
            break;
        default: 
            cout << "Error on color type." << endl;
            exit(1);
    }

    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    associated.box.w = surface->w;
    associated.box.h = surface->h;
    SDL_FreeSurface(surface);
}

Text::Text(GameObject &associated, 
           string fontFile, 
           int fontSize, 
           Text::TextStyle style, 
           string text,
           SDL_Color color,
           int OffsetX,
           int OffsetY) : Component(associated), fontFile(fontFile), fontSize(fontSize), style(style),
            text(text), color(color), texture(nullptr), on(true), alpha(255), timer(*new Timer()), OffsetX
            (OffsetX), OffsetY(OffsetY) {
    RemakeTexture();
}

Text::~Text() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

}

void Text::SetText(string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(Text::TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(string fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}
