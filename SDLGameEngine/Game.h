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
#include "Player.h"
#include "Camera.h"
#include "GameStateMachine.h"

class Game{
public:    
    static Game* Instance();
    SDL_Renderer* getRenderer() const;
    
    bool init(const char* title,
              int xpos, int ypos,
              int width, int height, int flags);
    
    
    void render();
    void update();
    void handleEvents();
    void quit();
    void clean();
    
    GameStateMachine* getStateMachine();
    
    bool running();
    void setTitle(string title);
    
    int getGameWidth() const;
    int getGameHeight() const;
    int getMapWidth();

    
    int getMapHeight();
    
    void setMapHeight(int mapHeight);
    void setMapWidth(int mapWidth);
    
    double getZoom() const;
    void setZoom(double zoom);
    
    void setPlayer(Player* player);
    
    Player* getPlayer();
    
    void setLiveMode(bool liveMode);
    bool isLiveModeOn();
    
private:
    ~Game();
    Game();
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




