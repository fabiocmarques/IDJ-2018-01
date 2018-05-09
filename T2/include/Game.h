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
#include <ctime>
#include <stack>

using namespace std;

#ifndef T1_GAME_H
#define T1_GAME_H

class Game {

    int frameStart;
    float dt;

    static Game *instance;

    State* storedState;
    SDL_Window* window;
    SDL_Renderer* renderer;

    stack<unique_ptr<State>> stateStack;

    void CalculateDeltaTime();

public:
    Game(string title, int width, int height);
    ~Game();

    static Game& GetInstance();
    SDL_Renderer* GetRenderer();
    State& GetCurrentState();

    void Push(State* state);

    void Run();

    float GetDeltaTime();
};




#endif //T1_GAME_H
