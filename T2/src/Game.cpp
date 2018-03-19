//
// Created by fabio on 14/03/18.
//

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "../include/Game.h"

Game *Game::instance = nullptr;

Game& Game::GetInstance() {

    if(Game::instance == nullptr){
        instance = new Game("Fabio Marques - 140039082", STD_WIDTH, STD_HEIGHT);
    }

    return *instance;
}

Game::Game(string t, int w, int h) {

    int img_flags = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    if(instance != nullptr){
        cout << "Existing Game instance when the constructor is called.";
        exit(1);
    }

    instance = this;

    // Inicializando a SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        cout << "Error on initializing SDL (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER).";
        cout << "Last error message: " << SDL_GetError();
        exit(1);
    }

    // Carregando loaders de formato de imagens
    if(IMG_Init(img_flags) != img_flags){
        cout << "Error on initializing SDL (img_flags).";
        cout << "Last error message: " << SDL_GetError();
        exit(1);
    }


    // Carregando loaders de audio, por default 0 ja vem com ".wav"
    Mix_Init(0);
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0){
        cout << "Fail on initializing audio frequency, format, channels and chunk size.";
        exit(1);
    }
    // Aumentando numero de canais alocados para 32
    Mix_AllocateChannels(32);

    // Inicializando a janela
    window = SDL_CreateWindow(t.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    if(window == nullptr){
        cout << "Fail on creating window.";
        exit(1);
    }

    // Criando o renderizador da janela
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        cout << "Fail on creating renderer.";
        exit(1);
    }

    state = new State();
}

Game::~Game(){
    // Deleta State
    delete state;

    // Para o audio
    Mix_CloseAudio();
    Mix_Quit();

    // Encerra imagens
    IMG_Quit();

    // Destroi janela e renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Encerra SDL
    SDL_Quit();

}

State& Game::GetState() {
    return *state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    cout << "Chegou no run." << endl;
    while(!state->QuitRequested()){
        state->Update(0);
        state->Render();

        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}
