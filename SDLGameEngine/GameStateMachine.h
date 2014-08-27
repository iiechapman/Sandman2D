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
#include "IGameState.h"

class GameStateMachine{
public:
    
    void update();
    void render();
    
    void pushState(IGameState* pState);
    void changeState(IGameState* pState);
    void popState();
    
    IGameState* getCurrentState(){
        return m_gameStates.back();
    }
    
private:
    vector<IGameState*> m_gameStates;
};


#endif /* defined(__SDLGameDevelopmentChapter1__GameStateMachine__) */
