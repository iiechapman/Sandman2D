//
//  EventManager.h
//  SDLGameEngine
//
//  Created by Evan Chapman on 8/3/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameEngine__EventManager__
#define __SDLGameEngine__EventManager__

#include <iostream>
#include <vector>
#include <map>
#include "InputHandler.h"

using namespace std;


class EventManager{
public:
    static EventManager* Instance(){
        if (!s_pInstance){
            s_pInstance = new EventManager();
        }
        return s_pInstance;
    }

    void receiveEvent
    (vector<EventHandler*> targets,string event, int argCount , vector<string> arguments);
    
    void addHandler(EventHandler* handler);
    void removeHandler(EventHandler* handler);
    
    ~EventManager();
private:
    EventManager();
    
    void handleEvent(vector<EventHandler*> targets,string event, int argCount , vector<string> arguments);
    
    static EventManager* s_pInstance;
    
    vector<EventHandler*> m_Handlers;
    
};

#endif /* defined(__SDLGameEngine__EventManager__) */
