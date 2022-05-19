#pragma once
#include "TextureManager.h"

class Map
{
private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;

public:
    Map(const char *path, SDL_Renderer *ren);
    void render();
};

Map::Map(const char *path, SDL_Renderer *ren)
{
    renderer = ren;
    texture = TextureManager::LoadTexture(path, ren);
}

void Map::render()
{
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}