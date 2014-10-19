//
//  GameOverState.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__GameOverState__
#define __SDLGameDevelopmentChapter1__GameOverState__

#include <iostream>
#include <vector>
#include "IGameObject.h"
#include "MenuState.h"

using namespace std;

class GameOverState : public MenuState{
    
public:
    ~GameOverState();
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual string getStateID() const { return s_gameOverID; }
    
    void setCallbacks(const vector<Callback>& callbacks);
    
private:
    static const string s_gameOverID;
    vector<IGameObject*> m_gameObjects;
    
    static void s_RestartButton();

    
};

#endif /* defined(__SDLGameDevelopmentChapter1__GameOverState__) */






















































//END