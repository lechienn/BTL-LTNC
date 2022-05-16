#include "library.h"
#include "skill.h"
#include "TextureManager.h"


class GameObject{
private:
    int xPos;
    int yPos;

    int HP;
    int angle = 45;
    int power = 0;
    bool direction;
    
    int frame = 0;
    

    SDL_Texture* objectTexture;
    SDL_Rect srcRect[6];
    SDL_Rect destRect;
    SDL_Renderer* renderer;

public:
    Skill skill;
    GameObject(const char* textureSheet, SDL_Renderer* ren, bool direc, const int &x, const int &y, const int &hpBarX, const int &hpBarY);
    ~GameObject();
    
    SDL_Rect getRect(){return destRect;}
    int getAngle(){return angle;}
    int getPower(){return power;}
    bool getDirection(){return direction;}
    int getHP(){return HP;}
    void setHP(int HP);

    // bool getTriggerSkill2(){return skill.triggerIncreaseDamage;}
   
    void setPower(int power);
    void setFrame(int frame);

    void handleEvent(SDL_Event &event, bool &isFire, bool &player1Turn);
    void update();
    void render();
    void renderAngle();
};

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren, bool direc, const int &x, const int &y, const int &hpBarX, const int &hpBarY){
    renderer = ren;
    objectTexture = TextureManager::LoadTexture(textureSheet, ren);
    xPos = x;
    yPos = y;
    direction = direc;
    HP = 100;

    skill.init(ren, hpBarX, hpBarY);

    srcRect[0].h = 200;
    srcRect[0].w = 150;
    srcRect[0].x = 0;
    srcRect[0].y = 0;

    srcRect[1].h = 200;
    srcRect[1].w = 150;
    srcRect[1].x = 150;
    srcRect[1].y = 0;

    srcRect[2].h = 200;
    srcRect[2].w = 150;
    srcRect[2].x = 300;
    srcRect[2].y = 0;

    srcRect[3].h = 200;
    srcRect[3].w = 150;
    srcRect[3].x = 450;
    srcRect[3].y = 0;

    srcRect[4].h = 200;
    srcRect[4].w = 150;
    srcRect[4].x = 600;
    srcRect[4].y = 0;

    srcRect[5].h = 200;
    srcRect[5].w = 150;
    srcRect[5].x = 750;
    srcRect[5].y = 0;

}
GameObject::~GameObject(){}

void GameObject::handleEvent(SDL_Event &event, bool &isFire, bool &player1Turn){
    

    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
            case SDLK_ESCAPE:
                HP = 0;
            case SDLK_LEFT: 
                xPos--; 
                // direction = false; 
                break;
            case SDLK_RIGHT: 
                xPos++;
                // direction = true;
                break;
            case SDLK_UP: 
                if(angle < 90) angle++; 
                
                break;
            case SDLK_DOWN: 
                if(angle > 0 ) angle--; 
                
                break;
            case SDLK_1:
                if(skill.doubleShoot) {
                    skill.triggerDoubleShoot = true;
                    skill.doubleShoot = false;
                }
                break;
            case SDLK_2:
                if(skill.increaseDamage) {
                    skill.triggerIncreaseDamage = true;
                    skill.increaseDamage = false;
                }
                break;
            case SDLK_3:
                if(skill.heal) {
                    HP>=80? HP=100 : HP+=20;
                    skill.heal = false;
                    player1Turn = !player1Turn;
                }
                break;
            case SDLK_SPACE: 
                power++; 
                frame = 2;
                break;
        }
    }
    else if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym){
            case SDLK_SPACE:
                isFire = !isFire;
                frame = 3;
                break;
        }
    }
}

void GameObject::update(){

    destRect.x = xPos;
    destRect.y = yPos;
    destRect.h = heightCharacter;
    destRect.w = widthCharacter;
}

void GameObject::render(){
    skill.render();
    SDL_RenderCopy(renderer, objectTexture, &srcRect[frame], &destRect);
}

// void GameObject::setAngle(int angle){
//     this->angle = angle; 
// }
void GameObject::setPower(int power){
    this->power = power;
}

void GameObject::setHP(int HP){
    if(HP < 0) this->HP = 0;
    else this->HP = HP;
}

void GameObject::renderAngle(){
        float x = (float)xPos + (float)widthCharacter/2;
        float y = (float)yPos + (float)heightCharacter/2;
    
        float xBegin, xEnd, yBegin, yEnd;
        float rad = direction?(((float)angle/180) * M_PI):(M_PI - ((float)angle/180) * M_PI);
        xBegin = x + cos(rad) * 90;
        yBegin = y - sin(rad) * 90;
        xEnd = x + cos(rad) * 180;
        yEnd = y - sin(rad) * 180;
    
        SDL_RenderDrawLine(renderer, (int)xBegin, (int)yBegin, (int)xEnd, (int)yEnd);
}

void GameObject::setFrame(int frame){
    this->frame = frame;
}