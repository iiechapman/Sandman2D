// ============================================================================
// [Include Section]
// ============================================================================
#include <SDL2/SDL.h>
#include "Game.h"
#include <unistd.h>
#include <stdio.h>


const int VERSION_NUMBER = 0;
const int BUILD_NUMBER = 3;
const int DESIRED_FPS = 60;
const int DELAY_TIME = 1000.0f / DESIRED_FPS;
const int GAME_WIDTH = 1024;
const int GAME_HEIGHT = 576;

int main(int argc, char* args[]){
    
    Uint32 frameStart,frameTime;
    Uint32 secondTimer = 0;
    int totalFrames = 0;
    int FPS = 0;
    
    //Capture and print the current working directory
    char filenameMax[FILENAME_MAX];
    getcwd(filenameMax, sizeof(filenameMax));
    cout << "Current working directory: " << filenameMax << endl;
    
    //If Game Inititalizes, beging game loop
    if (Game::Instance()->init
        ("Sandman Engine",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
         GAME_WIDTH, GAME_HEIGHT , SDL_RENDERER_ACCELERATED)){
            
            cout << "Game init success\n";
            
            //Begin Game Loop
            while(Game::Instance()->isRunning()){
                string title = "Sandman Engine Build: "
                + to_string(VERSION_NUMBER) + "." + to_string(BUILD_NUMBER)
                + " FPS: "+ to_string(FPS);
                
                //Capture time before update
                frameStart = SDL_GetTicks();
                
                //Game Loop
                Game::Instance()->handleEvents();
                Game::Instance()->update();
                Camera::Instance()->update();
                Game::Instance()->render();
                
                //Count frames and frametime after update
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
            //End Game Loop
            cout << "Game ended, cleaning up\n";
            Game::Instance()->clean();
        } else {
            //If game doesn't initialize, exit
            cout << "Game init fail - " << SDL_GetError() << endl;
            return -1;
        }
    
    return 0;
}


























//END