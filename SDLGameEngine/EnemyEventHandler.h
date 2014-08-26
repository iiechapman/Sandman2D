//
//  EnemyEventHandler.h
//  SDLGameEngine
//
//  Created by Evan Chapman on 8/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameEngine__EnemyEventHandler__
#define __SDLGameEngine__EnemyEventHandler__

#include <iostream>
#include "EventHandler.h"

class EnemyEventHandler : public EventHandler {
public:
    virtual void handleEvent(string event, int argCount, vector<string> arguments) = 0;
    
    
};


#endif /* defined(__SDLGameEngine__EnemyEventHandler__) */
