#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "menu.h"
Game *game = nullptr;
Menu *menu = nullptr;

int main(int argc, char *argv[])
{
    menu = new Menu();

    while (menu->running())
    {
        menu->handleEvent();
        if (menu->start())
        {
            const int FPS = 60;
            const int frameDelay = 1000 / FPS;
            Uint32 frameStart;
            int frameTime;

            game = new Game();
            game->init();
            while (game->running())
            {

                frameStart = SDL_GetTicks();

                game->handleEvent();
                game->update();
                game->render();

                frameTime = SDL_GetTicks() - frameStart;

                if (frameDelay > frameTime)
                {
                    SDL_Delay(frameDelay - frameTime);
                }
            }

            game->clean();
            delete game;
            menu->endGame();
        }
        menu->render();
    }
    menu->clean();
    delete menu;
    return 0;
}

