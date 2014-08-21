//
//  EventManager.h
//  SDLGameEngine
//
//  Created by Evan Chapman on 8/3/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameEngine__EventManager__
#define __SDLGameEngine__EventManager__

#define EVENT_TYPE_BROADCAST 0

#include <iostream>
#include <vector>
#include <map>
#include "EventHandler.h"
#include "Event.h"
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
    (vector<EventHandler*> targets,Event* event, int argCount , vector<string> arguments);
    
    void receiveEvent(vector<Event*>* events);
    
    void addHandler(EventHandler* handler);
    void removeHandler(EventHandler* handler);
    
    ~EventManager();
private:
    EventManager();
    
    void handleEvent(vector<EventHandler*> targets,Event* event, int argCount , vector<string> arguments);
    void handleEvent(vector<Event*>* events);
    
    static EventManager* s_pInstance;
    
    vector<EventHandler*> m_Handlers;
    vector<Event*> m_eventQueue;
    
};

#endif /* defined(__SDLGameEngine__EventManager__) */
