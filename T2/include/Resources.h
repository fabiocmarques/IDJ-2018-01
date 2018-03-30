//
// Created by fabio on 29/03/18.
//

#ifndef T2_RESOURCES_H
#define T2_RESOURCES_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <string>
#include <unordered_map>

using namespace std;


class Resources {
    static unordered_map<string, SDL_Texture*> imageTable;
    static unordered_map<std::string, Mix_Music*> musicTable;
    static unordered_map<std::string, Mix_Chunk*>  soundTable;

public:
    static SDL_Texture* GetImage(string file);
    static void ClearImages();

    static Mix_Music* GetMusic(string file);
    static void ClearMusics();

    static Mix_Chunk* GetSound(string file);
    static void ClearSounds();
};


#endif //T2_RESOURCES_H
