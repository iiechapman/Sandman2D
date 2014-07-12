//
//  GameState.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__GameState__
#define __SDLGameDevelopmentChapter1__GameState__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GameState{
    
public:
    virtual ~GameState() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    
    virtual string getStateID() const = 0;
    
protected:
    vector<string> m_textureIDList;
    
};

#endif /* defined(__SDLGameDevelopmentChapter1__GameState__) */
