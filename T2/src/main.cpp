//
// Created by fabio on 15/03/18.
//
#include <fstream>
#include <iostream>
#include <string>
#include <Game.h>
#include <StageState.h>

using namespace std;

int main(int argc, char** argv){
    Game& g = Game::GetInstance();
    g.Push(new StageState());
    g.Run();

    return 0;
}