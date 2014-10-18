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
#include "IGameObject.h"
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
    virtual string getStateID() const { return s_playID; }
    
    void setLiveMode(bool liveMode);
    bool liveModeOn();
    
    Level* getLevel();
    
    map<string,string>* getLevelFiles();
    
    vector<IGameObject*>* getGameObjects();
    map<string,GameObjectParams*>* getElements();
    
private:
    void loadNextLevel();
    
    static const string s_playID;
    vector<IGameObject*> m_gameObjects;
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






















































//END