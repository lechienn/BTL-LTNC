#include "library.h"

#include "TextureManager.h"
#include <iomanip>
#include <ctime>
#include <sstream>

// TTF_Font* winSpeedFont = TTF_OpenFont( "font/FS-Angry-Birds.ttf", 28 );
SDL_Color winSpeedColor = {0, 0, 0};
SDL_Rect winSpeedRect = {624, 45, 35, 25};
SDL_Texture *winSpeedTexture = NULL;
SDL_Rect winDirect = {605, 40, 65, 45};
SDL_Rect winLeft = {0, 0, 199, 100};
SDL_Rect winRight = {200, 0, 200, 100};

template <typename T>
std::string tostr(const T &t)
{
    std::ostringstream os;
    os << t;
    return os.str();
}

class Weapon
{
private:
    int xPos;
    int yPos;
    int velocityX;
    int velocityY;

    double winSpeed;

    SDL_Texture *weaponTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer *renderer;

    SDL_Texture *winDirection;
    Mix_Chunk *hitSound = NULL;

public:
    Weapon(const char *path, SDL_Renderer *ren);
    ~Weapon();

    void move(Uint32 &time, bool &player1Turn, bool &isFire, GameObject *player, GameObject *enermy);
    void update();
    void render();
    void renderWinSpeed();
};

Weapon::Weapon(const char *path, SDL_Renderer *ren)
{
    renderer = ren;
    weaponTexture = TextureManager::LoadTexture(path, ren);
    srand(time(0));
    winSpeed = (rand() % maxWinSpeed / 10.0) * ((rand() % 2 == 1) ? 1.0 : -1.0);
    winDirection = TextureManager::LoadTexture("img/win.png", ren);
    hitSound = Mix_LoadWAV("sound/bonk.wav");
}

Weapon::~Weapon()
{
    Mix_FreeChunk(hitSound);
    hitSound = NULL;
}

void Weapon::move(Uint32 &time, bool &player1Turn, bool &isFire, GameObject *player, GameObject *enermy)
{
    int currentTime = SDL_GetTicks() - time;
    int x, y;
    int targetX, targetY;
    int angle, power;
    double direction;

    int damage = 25;
    if (player->skill.triggerIncreaseDamage)
    {
        damage = 40;
    }

    x = player->getRect().x + widthCharacter / 2;
    y = player->getRect().y + heightCharacter / 2;
    targetX = enermy->getRect().x;
    targetY = enermy->getRect().y;
    angle = player->getAngle();
    direction = player->getDirection() ? 1 : -1;
    power = player->getPower() + direction * (int)(winSpeed * 6);

    // 0.09, 0.01
    yPos = y - direction * (double)power * sin(direction * M_PI * (double)angle / 180) * (double)currentTime * 0.09 + 0.008 * (double)currentTime * (double)currentTime;
    xPos = x + direction * (double)power * cos(direction * M_PI * (double)angle / 180) * (double)currentTime * 0.07;
    // std::cout << " " << xPos << "-" << yPos << " ";

    // if weapon goes out of screen
    if (xPos >= SCREEN_WIDTH || xPos <= 0 || yPos >= 600)
    {
        isFire = false;
        if (!player->skill.triggerDoubleShoot)
            player1Turn = !player1Turn;
        player->setPower(0);
        // enermy->setPower(0);
        player->setFrame(0);
        enermy->setFrame(4);
        time = 0;
        // winSpeedTexture = NULL;
        if (player->skill.triggerIncreaseDamage)
        {
            player->skill.triggerIncreaseDamage = false;
        }
        if (player->skill.triggerDoubleShoot)
        {
            player->skill.triggerDoubleShoot = false;
        }
        winSpeed = rand() % maxWinSpeed / 10.0 * ((rand() % 2 == 1) ? 1.0 : -1.0);
    }

    // if weapon hit enermy

    if ((xPos >= targetX && xPos <= targetX + widthCharacter) && (yPos >= targetY && yPos <= targetY + heightCharacter))
    {
        Mix_PlayChannel(-1, hitSound, 0);
        isFire = false;
        if (!player->skill.triggerDoubleShoot)
            player1Turn = !player1Turn;
        player->setPower(0);
        time = 0;
        enermy->setHP(enermy->getHP() - damage);
        player->setFrame(0);
        enermy->setFrame(5);
        // winSpeedTexture = NULL;
        if (player->skill.triggerIncreaseDamage)
        {
            player->skill.triggerIncreaseDamage = false;
        }
        if (player->skill.triggerDoubleShoot)
        {
            player->skill.triggerDoubleShoot = false;
        }
        winSpeed = rand() % maxWinSpeed / 10.0 * ((rand() % 2 == 1) ? 1.0 : -1.0);
    }
}

void Weapon::update()
{
    srcRect.h = 100;
    srcRect.w = 100;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xPos;
    destRect.y = yPos;
    destRect.h = 30;
    destRect.w = 30;
}

void Weapon::render()
{

    SDL_RenderCopy(renderer, weaponTexture, &srcRect, &destRect);
}

void Weapon::renderWinSpeed()
{
    winSpeedTexture = TextureManager::LoadTextureFromText(tostr(fabs(winSpeed)).c_str(), font, winSpeedColor, renderer);
    // std::cout << std::to_string(winSpeed).c_str();
    SDL_RenderCopy(renderer, winDirection, winSpeed >= 0 ? &winRight : &winLeft, &winDirect);
    SDL_RenderCopy(renderer, winSpeedTexture, NULL, &winSpeedRect);
}