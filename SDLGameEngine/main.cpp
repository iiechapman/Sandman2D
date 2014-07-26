// ============================================================================
// [Include Section]
// ============================================================================
#include <SDL2/SDL.h>
#include "Game.h"
#include <unistd.h>
#include <stdio.h>

const int BUILD_NUMBER = 0002;
const int DESIRED_FPS = 60;
const int DELAY_TIME = 1000.0f / DESIRED_FPS;
const int GAME_WIDTH = 1024;
const int GAME_HEIGHT = 576;

int main(int argc, char* args[]){
    
    Uint32 frameStart,frameTime;
    Uint32 secondTimer = 0;
    int totalFrames = 0;
    int FPS = 0;
    
    char filenameMax[FILENAME_MAX];
    
    
    getcwd(filenameMax, sizeof(filenameMax));
    
    cout << "Current working directory: " << filenameMax << endl;
    
    if (Game::Instance()->init("Sandman Engine" ,
                 SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               GAME_WIDTH, GAME_HEIGHT , SDL_RENDERER_ACCELERATED)){
        cout << "Game init success\n";
        
        while(Game::Instance()->running()){
            string title = "Sandman Engine Build: " + to_string(BUILD_NUMBER)
            + " FPS: "+ to_string(FPS);
            
            frameStart = SDL_GetTicks();
            
            Game::Instance()->handleEvents();
            Game::Instance()->update();
            Camera::Instance()->update();
            Game::Instance()->render();
            
            //Count frames and frametime
            totalFrames++;
            frameTime = SDL_GetTicks() - frameStart;
            
            //Count seconds
            secondTimer += frameTime;
            if (secondTimer >= 1000){
                FPS = totalFrames;
                Game::Instance()->setTitle(string(title));
                secondTimer = 0;
                totalFrames = 0;
            }
            
            //Delay processing to match desired FPS
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