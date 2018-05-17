//
// Created by Fabio Marques on 16/05/2018.
//

#ifndef T2_TEXT_H
#define T2_TEXT_H

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF

#include "SDL_include.h"
#include "Component.h"

using namespace std;

class Text : public Component{

public:
    enum TextStyle{
        SOLID,
        SHADED,
        BLENDED
    };

    Text(GameObject& associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color);
    ~Text();

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void SetText(string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(string fontFile);
    void SetFontSize(int fontSize);

private:
    TTF_Font* font;
    SDL_Texture* texture;

    string text;
    TextStyle style;
    string fontFile;
    int fontSize;
    SDL_Color color;


    void RemakeTexture();

};


#endif //T2_TEXT_H
