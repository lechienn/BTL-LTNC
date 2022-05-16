#pragma once
#include "Game.h"

class TextureManager{

public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren){
        SDL_Surface* surface = IMG_Load(fileName);
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
        SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
        SDL_FreeSurface(surface);

        return texture;
    }

    static SDL_Texture* LoadTextureFromText(const char* text, TTF_Font *font, SDL_Color color, SDL_Renderer *ren){
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
        if( textSurface == NULL )printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, textSurface);
        SDL_FreeSurface(textSurface);
        
        return texture;
    }
};