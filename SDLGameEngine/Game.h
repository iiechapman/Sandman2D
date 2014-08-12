//
//  Game.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/20/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__Game__
#define __SDLGameDevelopmentChapter1__Game__

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "GameStateMachine.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Camera.h"


class Game{
public:
    ~Game() {};
    
    static Game* Instance();
    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    
    bool init(const char* title,
              int xpos, int ypos,
              int width, int height, int flags);
    
    
    void render();
    void update();
    void handleEvents();
    void quit();
    void clean();
    
    GameStateMachine* getStateMachine(){ return m_pGameStateMachine;}
    
    bool running();
    
    int getGameWidth() const{
        return m_gameWidth;
    }
    int getGameHeight() const{
        return m_gameHeight;
    }
    int getMapWidth() {
        return m_mapWidth;
    }
    
    void setTitle(string title);
    
    int getMapHeight(){
        return m_mapHeight;
    }
    
    void setMapHeight(int mapHeight){
        m_mapHeight = mapHeight;
    }
    
    void setMapWidth(int mapWidth){
        m_mapWidth = mapWidth;
    }
    
    double getZoom() const{
        return m_zoom;
    }
    void setZoom(double zoom){
        m_zoom = zoom;
    }
    
    void setPlayer(Player* player){
        m_Player = player;
        
        Camera::Instance()->setTarget(&player->GetParams().getPosition());
        cout << "Camera locked to player\n";
    }
    Player* getPlayer(){
        return m_Player;
    }
    
    void setLiveMode(bool liveMode){
        m_bLiveMode = liveMode;
    }
    bool isLiveModeOn(){
        return m_bLiveMode;
    }
private:
    Game() {};
    static Game* s_pInstance;
    
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    
    int m_currentFrame;
    int m_gameWidth;
    int m_gameHeight;
    int m_mapWidth;
    int m_mapHeight;
    double m_zoom;
    
    
    vector<GameObject*> m_gameObjects;
    
    bool m_bRunning;
    bool m_bLiveMode = false;
    
    Player* m_Player;
    
    GameStateMachine* m_pGameStateMachine;
};



#endif /* defined(__SDLGameDevelopmentChapter1__Game__) */




