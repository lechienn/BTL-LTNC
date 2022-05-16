#include "library.h"
#include "TextureManager.h"

struct Skill{

    bool doubleShoot;
    bool increaseDamage;
    bool heal;
    bool triggerIncreaseDamage;
    bool triggerDoubleShoot;

    SDL_Texture *doubleShootTexture;
    SDL_Texture *increaseDamageTexture;
    SDL_Texture *healTexture;

    
    SDL_Rect doubleShootRect, increaseDamageRect, healRect;

    SDL_Renderer* renderer;

    Skill(){}
    void init(SDL_Renderer *ren, const int &x, const int &y);
    ~Skill();

    

    void setHeal(){heal = false;}
    void setIncreaseDamage(){increaseDamage = false;}
    void setDoubleShoot(){doubleShoot = false;}

    

    void update();
    void render();
};

void Skill::init(SDL_Renderer *ren, const int &x, const int &y){
    renderer = ren;
    doubleShoot = true;
    increaseDamage = true;
    heal = true;
    triggerIncreaseDamage = false;
    
    doubleShootTexture = TextureManager::LoadTexture("img/doubleShoot.png", ren);
    increaseDamageTexture = TextureManager::LoadTexture("img/increaseDamage.png", ren);
    healTexture = TextureManager::LoadTexture("img/heal.png", ren);

    //50 155-195 300-340 445-485 590 // 105 - 40
    doubleShootRect.x = x + 105;
    doubleShootRect.y = y + 50;
    doubleShootRect.w = 40;
    doubleShootRect.h = 40;

    increaseDamageRect.x = x + 105 + 40 + 105;
    increaseDamageRect.y = y + 50;
    increaseDamageRect.w = 40;
    increaseDamageRect.h = 40;

    healRect.x = x + 105 + 40 + 105 + 40 + 105;
    healRect.y = y + 50;
    healRect.w = 40;
    healRect.h = 40;
}

Skill::~Skill(){}

void Skill::update(){}

void Skill::render(){
    if(doubleShoot) SDL_RenderCopy(renderer, doubleShootTexture, NULL, &doubleShootRect);
    if(increaseDamage) SDL_RenderCopy(renderer, increaseDamageTexture, NULL, &increaseDamageRect);
    if(heal) SDL_RenderCopy(renderer, healTexture, NULL, &healRect);
}