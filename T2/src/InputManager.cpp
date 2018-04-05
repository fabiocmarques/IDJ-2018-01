//
// Created by fabio on 30/03/18.
//

#include "InputManager.h"

InputManager::InputManager() : updateCounter(0), quitRequested(false), mouseX(0), mouseY(0) {
    for (int i = 0; i < 416; ++i) {
        keyState[i] = false;
        keyUpdate[i] = 0;

        if(i < 6){
            mouseState[i] = false;
            mouseUpdate[i] = false;
        }
    }
}


void InputManager::Update() {
    SDL_Event ev;
    ++updateCounter;

    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;

    while(SDL_PollEvent(&ev)){


        if(ev.type == SDL_KEYDOWN){
            if(ev.key.repeat != 1){
                if(ev.key.keysym.sym >= 0x40000000 && ev.key.keysym.sym <= 0x4000011A){
                    keyState[ev.key.keysym.sym - 0x3FFFFF81] = true;
                    keyUpdate[ev.key.keysym.sym - 0x3FFFFF81] = updateCounter;
                }

                if(ev.key.keysym.sym >= 0x0 && ev.key.keysym.sym <= 0x7F){
                    keyState[ev.key.keysym.sym] = true;
                    keyUpdate[ev.key.keysym.sym] = updateCounter;
                }
            }


        }

        if(ev.type == SDL_KEYUP){
            if(ev.key.keysym.sym >= 0x40000000 && ev.key.keysym.sym <= 0x4000011A){
                keyState[ev.key.keysym.sym - 0x3FFFFF81] = false;
                keyUpdate[ev.key.keysym.sym - 0x3FFFFF81] = updateCounter;
            }

            if(ev.key.keysym.sym >= 0x0 && ev.key.keysym.sym <= 0x7F){
                keyState[ev.key.keysym.sym] = false;
                keyUpdate[ev.key.keysym.sym] = updateCounter;
            }
        }

        if(ev.type == SDL_MOUSEBUTTONDOWN){
            mouseState[ev.button.button] = true;
            mouseUpdate[ev.button.button] = updateCounter;
        }

        if(ev.type == SDL_MOUSEBUTTONUP){
            mouseState[ev.button.button] = false;
            mouseUpdate[ev.button.button] = updateCounter;
        }

        if(ev.type == SDL_QUIT){
            quitRequested = true;
        }


    }
}

bool InputManager::KeyPress(int key) {
    if(key >= 0x40000000 && key <= 0x4000011A){
        return (updateCounter == keyUpdate[key- 0x3FFFFF81] && keyState[key- 0x3FFFFF81]);
    } else {
        return (updateCounter == keyUpdate[key] && keyState[key]);
    }

}

bool InputManager::KeyRelease(int key) {
    if(key >= 0x40000000 && key <= 0x4000011A){
        return (updateCounter == keyUpdate[key- 0x3FFFFF81] && !keyState[key- 0x3FFFFF81]);
    } else {
        return (updateCounter == keyUpdate[key] && !keyState[key]);
    }
}

bool InputManager::IsKeyDown(int key) {
    if(key >= 0x40000000 && key <= 0x4000011A){
        return keyState[key - 0x3FFFFF81];
    } else {
        return keyState[key];
    }
}

bool InputManager::MousePress(int key) {
    return (updateCounter == mouseUpdate[key] && mouseState[key]);
}

bool InputManager::MouseRelease(int key) {
    return (updateCounter == mouseUpdate[key] && !mouseState[key]);
}

bool InputManager::IsMouseDown(int key) {
    return mouseUpdate[key];
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

InputManager &InputManager::GetInstance() {
    static InputManager IM;
    return IM;
}
