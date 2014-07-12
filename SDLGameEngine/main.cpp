// ============================================================================
// [Include Section]
// ============================================================================
#include <SDL2/SDL.h>
#include "Game.h"
#include <unistd.h>
#include <stdio.h>

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
const int GAME_WIDTH = 800;
const int GAME_HEIGHT = 600;

int main(int argc, char* args[]){
    
    Uint32 frameStart,frameTime;
    
    char filenameMax[FILENAME_MAX];
    
    
    getcwd(filenameMax, sizeof(filenameMax));
    
    cout << "Current working directory: " << filenameMax << endl;
    
    if (Game::Instance()->init("SDL Game Engine" ,
                 SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               GAME_WIDTH, GAME_HEIGHT , SDL_RENDERER_ACCELERATED)){
        cout << "Game init success\n";
        
        while(Game::Instance()->running()){
            
            frameStart = SDL_GetTicks();
            
            Game::Instance()->handleEvents();
            Game::Instance()->update();
            Game::Instance()->render();
            
            frameTime = SDL_GetTicks() - frameStart;
            
            if (frameTime < DELAY_TIME){
             SDL_Delay(int(DELAY_TIME - frameTime));
            }
            
            
        }
        cout << "Game ended, cleaning up\n";
        Game::Instance()->clean();
    } else {
        cout << "Game init fail - " << SDL_GetError() << endl;
        return -1;
    }

    return 0;
    
}






































































//END