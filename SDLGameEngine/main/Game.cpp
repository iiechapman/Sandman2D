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

    
    //Initialize video
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        //Successful init
        cout << "SDL Init successful\n";
        
        m_gameWidth = width;
        m_gameHeight = height;
        
        setGlobalZoom(3.0);
        
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
            
        } else {//SDL_CreateWindow() fail
            cout << "Window Creation fail \n";
            return false;
        }
    } else {//SDL_Init() fail
        cout << "SDL_Init fail\n";
        return false;
    }
    
    cout << "SDL Init success\n";

    //Register Object Factories for use by scripts
    GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    GameObjectFactory::Instance()->registerType("Light", new LightCreator());
    GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    GameObjectFactory::Instance()->registerType("Item", new ItemCreator());
    GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    
    
    //Init Game State and start on menu
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());
    
    InputHandler::Instance()->update();
    InputHandler::Instance()->initializeJoysticks();

    setRunning(true);
    
    return true;
}


void Game::setRunning(bool running){
    m_bRunning = running;
}

void Game::render(){
    //Render frame
    SDL_RenderClear(m_pRenderer); //Clear renderer
    
    m_pGameStateMachine->render(); //Render Current scene

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
    
    //Check for escape key to quit app
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)){
        SDL_SetWindowFullscreen(m_pWindow, SDL_FALSE);
    }
    
}

void Game::update(){
    //Capture current frame time
    m_currentFrame = int((SDL_GetTicks() / 100) % 6 );
    m_pGameStateMachine->update();
    SoundManager::Instance()->update();
}

void Game::quit(){
    m_bRunning = false;
}

bool Game::isRunning(){
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

GameStateMachine* Game::getStateMachine(){ return m_pGameStateMachine;}

SDL_Renderer* Game::getRenderer() const { return m_pRenderer; }

int Game::getGameWidth() const{
    return m_gameWidth;
}
int Game::getGameHeight() const{
    return m_gameHeight;
}

int Game::getMapWidth() {
    return m_mapWidth;
}

int Game::getMapHeight(){
    return m_mapHeight;
}

void Game::setMapHeight(int mapHeight){
    m_mapHeight = mapHeight;
}

void Game::setMapWidth(int mapWidth){
    m_mapWidth = mapWidth;
}

double Game::getGlobalZoom() const{
    return m_zoom;
}
void Game::setGlobalZoom(double zoom){
    m_zoom = zoom;
}

void Game::setPlayer(Player* player){
    m_Player = player;
    
    Camera::Instance()->setTarget(&player->GetParams().getPosition());
    cout << "Camera locked to player\n";
}

Player* Game::getPlayer(){
    return m_Player;
}

void Game::setLiveMode(bool liveMode){
    m_bLiveMode = liveMode;
}

bool Game::isLiveModeOn(){
    return m_bLiveMode;
}

Game::Game(){
    
}

Game::~Game(){
    
}


























































//END