//
// Created by fabio on 14/03/18.
//

#define STD_WIDTH 1024
#define STD_HEIGHT 600

#define INCLUDE_SDL
#include "SDL_include.h"

#include "State.h"

#include <string>
#include <iostream>

using namespace std;



#ifndef T1_GAME_H
#define T1_GAME_H

class Game {

    static Game *instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State *state;

    Game(string title, int width, int height);

public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
};




#endif //T1_GAME_H
