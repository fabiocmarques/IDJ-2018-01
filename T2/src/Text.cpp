//
// Created by Fabio Marques on 16/05/2018.
//

#include "Text.h"

void Text::Update(float dt) {

}

void Text::Render() {

}

bool Text::Is(string type) {
    return type == "Text";
}

void Text::RemakeTexture() {

}

Text::Text(GameObject &associated, string fontFile, int fontSize, Text::TextStyle style, string text, SDL_Color color) : Component(associated) {

}

Text::~Text() {

}

void Text::SetText(string text) {

}

void Text::SetColor(SDL_Color color) {

}

void Text::SetStyle(Text::TextStyle style) {

}

void Text::SetFontFile(string fontFile) {

}

void Text::SetFontSize(int fontSize) {

}
