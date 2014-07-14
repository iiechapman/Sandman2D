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
#include "GameObject.h"
#include "GameState.h"
#include "Level.h"

using namespace std;

class PlayState : public GameState{
    
public:
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
    
private:
    static const string s_playID;
    vector<GameObject*> m_gameObjects;
    
    Level* pLevel;
    string pLevelFile;
    
    bool m_LiveMode = false;
    bool m_EnteringLiveMode = false;
    

};

#endif /* defined(__SDLGameDevelopmentChapter1__PlayState__) */
