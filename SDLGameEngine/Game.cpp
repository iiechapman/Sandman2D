//
//  Game.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/20/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <SDL2_image/SDL_image.h>
#include "Game.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "GameObjectCreators.pch"
#include "MainMenuState.h"
#include "PlayState.h"
#include "SoundManager.h"

using namespace std;

Game* Game::s_pInstance = 0;

bool Game::init(const char* title,
                int xpos, int ypos,
                int width, int height, int flags){

    
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        //Successful init
        cout << "SDL Init successful \n";
        
        m_gameWidth = width;
        m_gameHeight = height;
        
        setZoom(3.0);
        
        m_pWindow = SDL_CreateWindow(title, xpos, ypos,
                                     width, height, flags);

        //Window creation successful
        if (m_pWindow != 0){
            cout << "Window creation success\n";
            m_pRenderer = SDL_CreateRenderer
            (m_pWindow, -1, SDL_RENDERER_ACCELERATED |
             SDL_RENDERER_PRESENTVSYNC
             | SDL_RENDERER_TARGETTEXTURE);
            
            //Render creation successful
            if (m_pRenderer != 0){
                cout << "Renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
            } else {
                cout << "Renderer creation fail\n";
                return false; //Renderer init fail
            }
            
        } else {
            cout << "Window Creation fail \n";
            return false; //Window creation fail
        }
    } else {
        cout << "SDL Init fail\n";
        return false; //SDL init fail
    }
    
    cout << "SDL Init success\n";

    
    GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    GameObjectFactory::Instance()->registerType("Light", new LightCreator());
    GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    
    
    //Init Game State and start on menu
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());
    
    InputHandler::Instance()->update();
    InputHandler::Instance()->initializeJoysticks();

    m_bRunning = true;
    
    return true;
}


void Game::render(){
    //Begin
    SDL_RenderClear(m_pRenderer); //Clear renderer
    
    m_pGameStateMachine->render();

    SDL_RenderPresent(m_pRenderer); //Draw to screen
}

void Game::handleEvents(){
    InputHandler::Instance()->update();

    //Check for level change button
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN) ||
        InputHandler::Instance()->getButtonState(0, XB_START_BUTTON)){
        m_pGameStateMachine->changeState(new PlayState());
    }
    
    //Check for fullscreen
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)){
        if ((SDL_GetWindowFlags(m_pWindow) & SDL_WINDOW_FULLSCREEN) == SDL_TRUE){
            cout << "Window is already fullscreen\n";
            SDL_SetWindowFullscreen(m_pWindow, SDL_FALSE);
        } else {
            SDL_SetWindowFullscreen(m_pWindow, SDL_TRUE);
            cout << "Turning fullscreen on\n";
        }
        
        
    }
    
    //Check for escape
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)){
        SDL_SetWindowFullscreen(m_pWindow, SDL_FALSE);
    }
    
    
    
}

void Game::update(){
    m_currentFrame = int((SDL_GetTicks() / 100) % 6 );

    m_pGameStateMachine->update();
    SoundManager::Instance()->update();
}

void Game::quit(){
    m_bRunning = false;
}

bool Game::running(){
    return m_bRunning;
}

void Game::clean(){
    cout << "Cleaning game\n";
    TextureManager::Instance()->clean();
    InputHandler::Instance()->clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::setTitle(string title){
    SDL_SetWindowTitle(m_pWindow, title.c_str());
}

Game* Game::Instance(){
    if (s_pInstance == 0){
        s_pInstance = new Game();
    }
    return s_pInstance;
}





































































//END