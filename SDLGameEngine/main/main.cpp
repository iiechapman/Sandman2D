//
//  main.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/20/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <SDL2/SDL.h>
#include "Game.h"
#include <unistd.h>
#include <cstdio>

// This is needed to detect bundle information for mac app
#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif


// const int VERSION_NUMBER = 0;
// const int BUILD_NUMBER = 3;
const int DESIRED_FPS = 60;
const int DELAY_TIME = 1000.0f / DESIRED_FPS;
const int GAME_WIDTH = 1024;
const int GAME_HEIGHT = 576;
const int INIT_FAIL = -1;
const int INIT_SUCCESS = 0;

char    title[FILENAME_MAX];
char    FILE_PATH[FILENAME_MAX];
Uint32  frameStart, frameTime;
Uint32  secondTimer = 0;
int     totalFrames = 0;
int     FPS = 0;

void  PrintWorkingDirectory();
void  CaptureAppleDirectory();
//char* GetWorkingDirectory();

void  GetWorkingDirectory();
void  CaptureWorkingDirectory(char* buffer);
void  CaptureStartTime();
void  CaptureTickTime();
void  Sync();


int main(int argc, char* args[]) {
    
    //Check for apple directory
#ifdef __APPLE__
    cout << "Checking Apple Directory structure\n";
    CaptureAppleDirectory();
    GetWorkingDirectory();
#endif
    
    PrintWorkingDirectory();
  
  // If Game Inititalizes, begin game loop
  if (Game::Instance()->init
      ("Sandman Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
       GAME_WIDTH, GAME_HEIGHT, SDL_RENDERER_ACCELERATED)) {
        cout << "Game init success\n";
        
        // Begin Game Loop
        while (Game::Instance()->isRunning()) {
          // title = "Sandman Engine Build: "
          // + to_string(VERSION_NUMBER) + "." + to_string(BUILD_NUMBER)
          // + " FPS: "+ to_string(FPS);
          CaptureWorkingDirectory(title);
          CaptureStartTime();
          
          // Game Loop
          Game::Instance()->handleEvents();
          Game::Instance()->update();
          Camera::Instance()->update();
          Game::Instance()->render();
          
          CaptureTickTime();
          Sync();
        }  // End Game Loop
        cout << "Game ended, cleaning up\n";
        Game::Instance()->clean();
        
      } else {
        cout << "Game init fail - " << SDL_GetError() << "\n";
        return INIT_FAIL;
      }
  return INIT_SUCCESS;

}


// Prints current directory app is executed from
void PrintWorkingDirectory() {
    char filenameMax[FILENAME_MAX];
    getcwd(filenameMax, sizeof(filenameMax));
    cout << "Current working directory:\n" << filenameMax << "\n";
}

void CaptureWorkingDirectory(char* buffer) {

    getcwd(buffer, sizeof(buffer));
    
    //cout << "Directory: " << buffer << "\n";
    if (!buffer){
        buffer = 0;
    }
}

// Capture time before update
void CaptureStartTime() {
    frameStart = SDL_GetTicks();
}

// Count frames, frametime, and seconds after update
void CaptureTickTime() {

    // Count frames and frametime after update
    totalFrames++;
    frameTime = SDL_GetTicks() - frameStart;
    
    // Count seconds
    secondTimer += frameTime;
    if (secondTimer >= 1000) {
        FPS = totalFrames;
        Game::Instance()->setTitle(title);

        secondTimer = 0;
        totalFrames = 0;
    }

  // Count frames and frametime after update
  totalFrames++;
  frameTime = SDL_GetTicks() - frameStart;
  
  // Count seconds
  secondTimer += frameTime;
  if (secondTimer >= 1000) {
    FPS = totalFrames;
    //printf("Title: %s", title);
    Game::Instance()->setTitle(title);
    secondTimer = 0;
    totalFrames = 0;
  }

}

// Delay processing to match desired FPS
void Sync() {
    if (frameTime < DELAY_TIME) {
        SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
    }
}



void CaptureAppleDirectory(){
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation
        (resourcesURL, TRUE, reinterpret_cast<UInt8*>(path), PATH_MAX)) {
        // error!
    }
    CFRelease(resourcesURL);
    
    chdir(path);
    std::cout << "Current Path: " << path << "\n";
#endif
}



// This makes relative paths work in C++ in Xcode by changing directory to the
// Resources folder inside the .app bundle
void GetWorkingDirectory() {
  CFBundleRef mainBundle = CFBundleGetMainBundle();
  CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
  char path[PATH_MAX];
  if (!CFURLGetFileSystemRepresentation
      (resourcesURL, TRUE, reinterpret_cast<UInt8*>(path), PATH_MAX)) {
    // error!
  }
  CFRelease(resourcesURL);
  
    chdir(path);
  std::cout << "Current Path: " << path << "\n";
}






