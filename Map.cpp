#include "Map.h"

Map::Map(const char* path, SDL_Renderer* ren){
    renderer = ren;
    texture = TextureManager::LoadTexture(path, ren);
}

void Map::render(){
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}