//
// Created by fabio on 29/03/18.
//

#include <Game.h>
#include "Resources.h"

using namespace std;

unordered_map<string, SDL_Texture*> Resources::imageTable = *new unordered_map<string, SDL_Texture*>;
unordered_map<std::string, Mix_Music*> Resources::musicTable = *new unordered_map<std::string, Mix_Music*>;
unordered_map<std::string, Mix_Chunk*> Resources::soundTable = *new unordered_map<std::string, Mix_Chunk*>;
unordered_map<std::string, TTF_Font*> Resources::fontTable = *new unordered_map<std::string, TTF_Font*>;

SDL_Texture *Resources::GetImage(string file) {
    SDL_Texture* tex = nullptr;
    unordered_map<string, SDL_Texture*>::const_iterator iterator = imageTable.find(file);

    if(iterator == imageTable.end()){
        tex = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if(tex == nullptr){
            cout << "Erro: " << SDL_GetError() << endl;
            cout << "Fail to open the image: " << file << " .";
            exit(1);
        }

        imageTable.emplace(file, tex);
        return imageTable.at(file);
    } else{
        return iterator->second;
    }

}

void Resources::ClearImages() {
    for(auto it = imageTable.begin(); it != imageTable.end(); ){
        SDL_DestroyTexture(it->second);
        it = imageTable.erase(it);
    }

    imageTable.clear();
}

Mix_Music* Resources::GetMusic(string file) {
    Mix_Music* music = nullptr;
    unordered_map<string, Mix_Music*>::const_iterator iterator = musicTable.find(file);

    if(iterator == musicTable.end()){
        music = Mix_LoadMUS(file.c_str());
        if(music == nullptr){
            cout << "Erro: " << SDL_GetError() << endl;
            cout << "Fail to open the image: " << file << " .";
            exit(1);
        }

        musicTable.emplace(file, music);
        return musicTable.at(file);
    } else{
        return iterator->second;
    }
}

void Resources::ClearMusics() {
    Mix_FadeOutMusic(0);

    for(auto it = musicTable.begin(); it != musicTable.end(); ){
        Mix_FreeMusic(it->second);
        it = musicTable.erase(it);
    }

    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(string file) {
    Mix_Chunk* sound = nullptr;
    unordered_map<string, Mix_Chunk*>::const_iterator iterator = soundTable.find(file);

    if(iterator == soundTable.end()){
        sound = Mix_LoadWAV(file.c_str());
        if(sound == nullptr){
            cout << "Erro: " << SDL_GetError() << endl;
            cout << "Fail to open the image: " << file << " .";
            exit(1);
        }

        soundTable.emplace(file, sound);
        return soundTable.at(file);
    } else{
        return iterator->second;
    }
}

void Resources::ClearSounds() {
    Mix_HaltChannel(-1);

    for(auto it = soundTable.begin(); it != soundTable.end(); ){
        Mix_FreeChunk(it->second);
        it =   soundTable.erase(it);
    }

    soundTable.clear();
}

TTF_Font* Resources::GetFont(string file, int size) {
    TTF_Font* font = nullptr;
    string key = file+to_string(size);
    unordered_map<string, TTF_Font*>::const_iterator iterator = fontTable.find(key);

    if(iterator == fontTable.end()){
        font = TTF_OpenFont(file.c_str(), size);
        if(font == nullptr){
            cout << "Erro: " << SDL_GetError() << endl;
            cout << "Fail to open the image: " << file << " .";
            exit(1);
        }

        fontTable.emplace(key, font);
        return fontTable.at(key);
    } else{
        return iterator->second;
    }
}

void Resources::ClearFonts() {

    for(auto it = fontTable.begin(); it != fontTable.end(); ){
        TTF_CloseFont(it->second);
        it = fontTable.erase(it);
    }

    fontTable.clear();
}
