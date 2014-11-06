// ============================================================================
// [Include Section]
// ============================================================================
#include <SDL2/SDL.h>
#include "Game.h"
#include <unistd.h>
#include <cstdio>

//This is needed to detect bundle information for mac app
#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif


//const int VERSION_NUMBER = 0;
//const int BUILD_NUMBER = 3;
const int DESIRED_FPS = 60;
const int DELAY_TIME = 1000.0f / DESIRED_FPS;
const int GAME_WIDTH = 1024;
const int GAME_HEIGHT = 576;

string title;
Uint32 frameStart,frameTime;
Uint32 secondTimer = 0;
int totalFrames = 0;
int FPS = 0;

void PrintWorkingDirectory();
string GetWorkingDirectory();
void CaptureStartTime();
void CaptureTickTime();
void Sync();

int main(int argc, char* args[]){
    
    // ----------------------------------------------------------------------------
    // This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        // error!
    }
    CFRelease(resourcesURL);
    
    chdir(path);
    std::cout << "Current Path: " << path << std::endl;
#endif
    // ----------------------------------------------------------------------------
    
    
    //Capture and print the current working directory
    //PrintWorkingDirectory();
    
    //If Game Inititalizes, begin game loop
    if (Game::Instance()->init
        ("Sandman Engine",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
         GAME_WIDTH, GAME_HEIGHT , SDL_RENDERER_ACCELERATED)){
            
            cout << "Game init success\n";
            
            //Begin Game Loop
            while(Game::Instance()->isRunning()){
                //                title = "Sandman Engine Build: "
                //                + to_string(VERSION_NUMBER) + "." + to_string(BUILD_NUMBER)
                //                + " FPS: "+ to_string(FPS);
                title = GetWorkingDirectory();
                CaptureStartTime();
                
                //Game Loop
                Game::Instance()->handleEvents();
                Game::Instance()->update();
                Camera::Instance()->update();
                Game::Instance()->render();
                
                CaptureTickTime();
                Sync();
            }
            //End Game Loop
            cout << "Game ended, cleaning up\n";
            Game::Instance()->clean();
        } else {
            //If game doesn't initialize, exit
            cout << "Game init fail - " << SDL_GetError() << "\n";
            return -1;
        }
    
    return 0;
}


//Prints current directory app is executed from
void PrintWorkingDirectory(){
    char filenameMax[FILENAME_MAX];
    getcwd(filenameMax, sizeof(filenameMax));
    cout << "Current working directory:\n" << filenameMax << "\n";
}

string GetWorkingDirectory(){
    char filenameMax[FILENAME_MAX];
    getcwd(filenameMax, sizeof(filenameMax));
    return filenameMax;
}



//Capture time before update
void CaptureStartTime(){
    frameStart = SDL_GetTicks();
}

//Count frames, frametime, and seconds after update
void CaptureTickTime(){
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
    
}

//Delay processing to match desired FPS
void Sync(){
    if (frameTime < DELAY_TIME){
        SDL_Delay(int(DELAY_TIME - frameTime));
    }
}
























//END