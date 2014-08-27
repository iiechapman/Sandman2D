//
//  PlayState.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__PlayState__
#define __SDLGameDevelopmentChapter1__PlayState__

#include <iostream>
#include <vector>
#include <map>
#include "GameObject.h"
#include "IGameState.h"
#include "Level.h"

class EventHandler;

using namespace std;

class PlayState : public IGameState{
    
public:
    PlayState();
    ~PlayState();
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    void setLiveMode(bool liveMode){
        m_LiveMode = liveMode;
    }
    bool liveModeOn(){
        return m_LiveMode;
    }
    
    virtual string getStateID() const { return s_playID; }
    
    Level* getLevel(){
        return pLevel;
    }
    
    map<string,string>* getLevelFiles(){
        return &pLevelFiles;
    }
    
    vector<GameObject*>* getGameObjects(){
        return &m_gameObjects;
    }
    map<string,GameObjectParams*>* getElements(){
        return &m_Elements;
    }
    
private:
    void loadNextLevel();
    
    static const string s_playID;
    vector<GameObject*> m_gameObjects;
    map<string,GameObjectParams*> m_Elements;
    
    int m_currentLevel = 0;
    Level* pLevel;
    map<string,string> pLevelFiles;
    
    bool m_bSwitchingLevels = false;
    bool m_LiveMode = false;
    bool m_EnteringLiveMode = false;
    bool m_bEnterHeld = false;
    
    EventHandler m_handler;
    
    //Camera Shake
    int rumbleFactor = 1;
    
    

};

#endif /* defined(__SDLGameDevelopmentChapter1__PlayState__) */
