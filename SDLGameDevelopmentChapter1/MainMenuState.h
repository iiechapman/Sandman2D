//
//  MainMenuState.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/17/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__MainMenuState__
#define __SDLGameDevelopmentChapter1__MainMenuState__

#include <iostream>
#include "MenuState.h"
#include "GameObject.h" 

using namespace std;

class MainMenuState : public MenuState{

public:
    MainMenuState();
    ~MainMenuState();
    
    void update();
    void render();
    
    bool onEnter();
    bool onExit();
    
    string getStateID() const {return s_mainMenuID;}

private:
    void setCallbacks(const vector<Callback>& callbacks);
    
    //Callbacks for menu items
    
    static void s_PlayButton();
    static void s_ExitButton();
    
    static const string s_mainMenuID;
    
    vector<GameObject*> m_gameObjects;
    
};



#endif /* defined(__SDLGameDevelopmentChapter1__MainMenuState__) */
