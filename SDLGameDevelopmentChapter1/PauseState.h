//
//  PauseState.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__PauseState__
#define __SDLGameDevelopmentChapter1__PauseState__

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "MenuState.h"

using namespace std;

class PauseState : public MenuState{
    
public:
    ~PauseState();
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual string getStateID() const { return s_pauseID; }
    
    void setCallbacks(const vector<Callback>& callbacks);
    
private:
    static const string s_pauseID;
    vector<GameObject*> m_gameObjects;
    
    static void s_ResumeButton();
    static void s_MenuButton();
    
    
};

#endif /* defined(__SDLGameDevelopmentChapter1__PauseState__) */
