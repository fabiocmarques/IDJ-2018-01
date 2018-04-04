//
// Created by fabio on 30/03/18.
//

#ifndef T2_INPUTMANAGER_H
#define T2_INPUTMANAGER_H

#define INCLUDE_SDL
#include "SDL_include.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT


class InputManager {
    InputManager();

    bool mouseState[6];
    int mouseUpdate[6];

    bool keyState[416];
    int keyUpdate[416];

    bool quitRequested;

    int updateCounter;

    int mouseX;
    int mouseY;

public:
    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int key);
    bool MouseRelease(int key);
    bool IsMouseDown(int key);

    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

    static InputManager& GetInstance();

};


#endif //T2_INPUTMANAGER_H
