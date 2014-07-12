//
//  GameStateMachine.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__GameStateMachine__
#define __SDLGameDevelopmentChapter1__GameStateMachine__

#include <iostream>
#include <vector>
#include "GameState.h"

class GameStateMachine{
public:
    
    void update();
    void render();
    
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    
    GameState* getCurrentState(){
        return m_gameStates.back();
    }
    
private:
    vector<GameState*> m_gameStates;
};


#endif /* defined(__SDLGameDevelopmentChapter1__GameStateMachine__) */
