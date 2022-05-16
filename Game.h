#ifndef GAME_H_
#define GAME_H_

#include "library.h"
// #include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Weapon.h"
#include "barProgress.h"



GameObject* player1;
GameObject* player2;
Map* map;
Weapon* weapon;
barProgress *player1HP;
barProgress *player2HP;
barProgress *powerBar;

Uint32 startFire = 0;

class Game{
private:
    bool isFire;
    bool player1Turn;
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    Game();
    ~Game();
    void init();
    void handleEvent();
    void update();
    void render();
    void clean();
    bool running() {return isRunning;}
};

Game::Game(){}

Game::~Game(){}

void Game::init(){
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    TTF_Init();
    font = TTF_OpenFont( "font/FS-Angry-Birds.ttf", 30 );
    
    isRunning = true;
    player1Turn = true;
    isFire = false;
    
    player1 = new GameObject("img/girl.png", renderer, true, 200, 450, 50, 40);
    player2 = new GameObject("img/boy.png", renderer, false, 800, 450, 690, 40);
    map = new Map("img/bg.png",renderer);
    weapon = new Weapon("img/rocktest.png", renderer);

    player1HP = new barProgress(renderer, "img/hpBar.png", 50, 40, 540, 40);
    player2HP = new barProgress(renderer, "img/hpBar.png", 690, 40, 540, 40);
    powerBar = new barProgress(renderer, "img/ruler-nobg.png", 140, 650, 1000, 50);
}

void Game::handleEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT: 
            isRunning = false;
            break;
        default:
            if(player1Turn){
                player1->handleEvent(event, isFire, player1Turn);
                break;
            }
            else {
                player2->handleEvent(event, isFire, player1Turn);
                break;
            }
    }
}

void Game::update(){
    if(isFire){
        if(startFire == 0)startFire = SDL_GetTicks();
        if(player1Turn) weapon->move(startFire, player1Turn ,isFire, player1, player2, player1->skill.triggerIncreaseDamage, player1->skill.triggerDoubleShoot);
        else weapon->move(startFire, player1Turn ,isFire, player2, player1, player2->skill.triggerIncreaseDamage, player2->skill.triggerDoubleShoot);
        weapon->update();
    }
    
    player1->update();
    player2->update();
    player1HP->update(player1->getHP(), true);
    player2HP->update(player2->getHP(), false);
    powerBar->update(player1Turn?player1->getPower():player2->getPower(), false);

    if(player1->getHP() == 0 || player2->getHP() == 0) {isRunning = false;}
}

void Game::render(){
    SDL_RenderClear(renderer);
    map->render();
    if(isFire){
        weapon->render();
    }
    
    player1->render();
    player2->render();
    player1HP->render();
    player2HP->render();
    if(!isFire) player1Turn?player1->renderAngle():player2->renderAngle();
    powerBar->render();
    weapon->renderWinSpeed();
    SDL_RenderPresent(renderer);

    if(player1->getHP() == 0 || player2->getHP() == 0) {
        SDL_Color color = {60, 60, 150, 0};
        SDL_Rect rect = {540, 200, 200, 100};
        
        SDL_Texture *notice = TextureManager::LoadTextureFromText(player1->getHP()==0?"Player 2 WIN!":"Player 1 WIN!", font, color, renderer);
        SDL_RenderCopy(renderer, notice, NULL, &rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);

    }
}

void Game::clean(){
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    delete player1;
    delete player2;
    delete weapon;
    delete powerBar;
    delete player1HP;
    delete player2HP;
    delete map;

    // IMG_Quit();
    
}

#endif