#include "library.h"
#include "Map.h"

class Menu{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isRunning;
    bool startGame;

    int menuItem = 2;
    SDL_Texture *menuBGTexture;
    
    SDL_Texture *choice1;
    SDL_Texture *choice2;

    SDL_Rect destRect1;
    int inside1;
    SDL_Rect destRect2;
    int inside2;

    SDL_Rect srcRect1[2];
    SDL_Rect srcRect2[2];

    Map* menu;

    Mix_Music *gMusic = NULL;
public:
    
    Menu();
    ~Menu();
    void handleEvent();
    void render();
    void clean();
    bool running() {return isRunning;}
    bool start() {return startGame;}
    void endGame() {startGame = false;}

    SDL_Window* getWindow(){return window;}
};

Menu::Menu(){
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    menu = new Map("img/bgMenu.png",renderer);
    choice1 = TextureManager::LoadTexture("img/menuPlayGame.png", renderer);
    choice2 = TextureManager::LoadTexture("img/menuQuit.png", renderer);

    isRunning = true;
    startGame = false;

    destRect1 = {505, 520, 270, 50};
    destRect2 = {580, 600, 120, 50};

    srcRect1[0] = {0, 0, 270, 50};
    srcRect1[1] = {270, 0, 270, 50};
    srcRect2[0] = {0, 0, 120, 50};
    srcRect2[1] = {120, 0, 120 ,50};

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    gMusic = Mix_LoadMUS( "sound/music.wav" );
    Mix_PlayMusic( gMusic, -1 );
}

Menu::~Menu(){}

void Menu::handleEvent(){
    SDL_Event event;
    int x, y;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT: 
            isRunning = false;
            break;
        case SDL_MOUSEMOTION:
            
            SDL_GetMouseState( &x, &y );
            if(x >= destRect1.x && x <= (destRect1.x + destRect1.w) && y >= destRect1.y && y <= (destRect1.y + destRect1.h)) inside1 = 1;
            else inside1 = 0;
            if(x >= destRect2.x && x <= (destRect2.x + destRect2.w) && y >= destRect2.y && y <= (destRect2.y + destRect2.h)) inside2 = 1;
            else inside2 = 0;
            break;
        case SDL_MOUSEBUTTONUP:
            
            SDL_GetMouseState( &x, &y );
            if(x >= destRect1.x && x <= (destRect1.x + destRect1.w) && y >= destRect1.y && y <= (destRect1.y + destRect1.h)) startGame = true;
            
            if(x >= destRect2.x && x <= (destRect2.x + destRect2.w) && y >= destRect2.y && y <= (destRect2.y + destRect2.h)) isRunning = false;
            break;
    }
}

void Menu::render(){
    SDL_RenderClear(renderer);
    menu->render();
    SDL_RenderCopy(renderer, choice1, &srcRect1[inside1], &destRect1);
    SDL_RenderCopy(renderer, choice2, &srcRect2[inside2], &destRect2);
    SDL_RenderPresent(renderer);
}

void Menu::clean(){
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    Mix_Quit();
    SDL_Quit();
}