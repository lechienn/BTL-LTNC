#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "menu.h"
Game *game = nullptr;
Menu *menu = nullptr;


int main(int argc, char* argv[]){
    menu = new Menu();

    while(menu->running()){
        menu->handleEvent();
        if(menu->start())
        {
            const int FPS = 60;
            const int frameDelay = 1000/FPS;
            Uint32 frameStart;
            int frameTime;

            game = new Game();
            game->init( );
            while(game->running()){
                
                frameStart = SDL_GetTicks();

                game->handleEvent();
                game->update();
                game->render();

                frameTime = SDL_GetTicks() - frameStart;
                
                if(frameDelay > frameTime){
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

//----------------------------------------//
/*
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const string WINDOW_TITLE = "Gunny fake"; 

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void test(SDL_Event e, Entity &ball, int x, int y);
// SDL_Texture* ballTexture = NULL;

bool mouseDown = false;
bool mousePressed = false;
SDL_Event event;

int main(int argc, char* argv[]){
    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer);
    
    Entity ball("img\\ballTest.png", window, renderer);
    Entity ball2("img\\ballTest.png", window, renderer);
    ball.loadTexture();
    ball.createImage();

    ball2.loadTexture();
    ball2.createImage();
    
    // int mouseX = 0;
	// int mouseY = 0;
    // do{
    // while (SDL_PollEvent(&event))
	// {
	// 	switch(event.type)
	// 	{
	// 	case SDL_MOUSEBUTTONDOWN:
    //     cout << "click\n";
	// 		if (event.button.button == SDL_BUTTON_LEFT)
	// 		{
	// 			SDL_GetMouseState(&mouseX, &mouseY);
    //             cout << mouseX << " " << mouseY << endl;
	// 			mousePressed = true;
	// 		}
	// 		break;
		
	// 	case SDL_MOUSEBUTTONUP:
	// 		if (event.button.button == SDL_BUTTON_LEFT)
	// 		{
				
	//             SDL_GetMouseState(&mouseX, &mouseY);
    //             cout << mouseX << " " << mouseY << endl;
	// 		}
	// 		break;
	// 	}
	// }
    test(event, ball, 5, 5);
    test(event, ball2, 10, -5);


    // SDL_RenderPresent(renderer);

    // waitUntilKeyPressed();

    SDL_Delay(5000);

    quitSDL(window, renderer);

    return 0;
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer){
    
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                SDL_RENDERER_PRESENTVSYNC);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void waitUntilKeyPressed(){
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
        (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
        return;
        SDL_Delay(100);
    }
}

void test(SDL_Event e, Entity &ball, int x, int y){
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
        (e.type == SDL_MOUSEBUTTONDOWN)){
            cout << "something";
            for(int i = 0; i < 50; i++)
            ball.render(x,y);
            return;
        }
        SDL_Delay(100);
    }
}

//--------------------PAINTER--------------------//

    // SDL_Texture* loadTexture( string path ){
    //     SDL_Texture* newTexture = NULL;
    //     SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    //     if ( loadedSurface == NULL )
    //         cout << "Unable to load image " << path << " SDL_image Error: "
    //               << IMG_GetError() << endl;
    //     else {
    //         newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    //         if( newTexture == NULL )
    //             cout << "Unable to create texture from " << path << " SDL Error: "
    //                 << SDL_GetError() << endl;
    //         SDL_FreeSurface( loadedSurface );
    //     }
    //     return newTexture;
    // }
    
    // bool createImage(SDL_Texture* texture){
    //     if( texture == NULL ) return false;
    //     SDL_RenderCopy( renderer, texture, NULL, NULL );
    //     return true;
    // }
//--------------------PAINTER--------------------//

*/