#pragma once
#include "library.h"

class barProgress
{
private:
    const int max = 100;

    SDL_Texture *barTexture;
    SDL_Rect srcRect, fullRect, restRect;
    SDL_Renderer *renderer;

public:
    // barProgress(SDL_Renderer *ren, const int &x, const int &y, const int &w, const int &h);

    barProgress(SDL_Renderer *ren, const char *path, const int &x, const int &y, const int &w, const int &h);
    // barProgress(SDL_Renderer *ren, );
    ~barProgress();
    void update(const int &number, const bool &leftPlayer);
    void render();
};

barProgress::barProgress(SDL_Renderer *ren, const char *path, const int &x, const int &y, const int &w, const int &h)
{
    renderer = ren;
    barTexture = TextureManager::LoadTexture(path, ren);
    srcRect = {x, y, w, h};
    fullRect = {x, y, w, h};
    restRect.y = y;
    restRect.h = h;
}

barProgress::~barProgress() {}

void barProgress::update(const int &number, const bool &fromLeft)
{

    restRect.w = (int)((float)fullRect.w * number / max);
    if (fromLeft)
        restRect.x = fullRect.x + (fullRect.w - restRect.w);
    else
        restRect.x = fullRect.x;
}

void barProgress::render()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 40);
    SDL_RenderFillRect(renderer, &fullRect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 60, 80, 255);
    SDL_RenderFillRect(renderer, &restRect);
    SDL_RenderCopy(renderer, barTexture, NULL, &fullRect);
}
