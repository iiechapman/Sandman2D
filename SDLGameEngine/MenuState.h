//
//  MenuState.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__MenuState__
#define __SDLGameDevelopmentChapter1__MenuState__

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "IGameState.h"

using namespace std;

class MenuState : public IGameState{
    
protected:
    typedef void(*Callback)();
    
    virtual void setCallbacks(const vector<Callback>& callbacks) = 0;
    
    vector<Callback> m_callbacks;
    
};

#endif /* defined(__SDLGameDevelopmentChapter1__MenuState__) */









































































//END