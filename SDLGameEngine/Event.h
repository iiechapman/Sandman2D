//
//  Event.h
//  SDLGameEngine
//
//  Created by Evan Chapman on 8/14/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameEngine__Event__
#define __SDLGameEngine__Event__

#include <iostream>
#include <vector>
#include "EventHandler.h"

using namespace std;

class Event{
public:
    
    Event(string caller, EventHandler* target, string eventName,
          int argCount, vector<string> arguments);
    
    string getCaller(){
        return m_caller;
    }
    
    EventHandler* getTarget(){
        return m_target;
    }
    
    string getEventName(){
        return m_eventName;
    }
    
    int getArgCount(){
        return m_argCount;
    }
    
    vector<string>* getArguments(){
        return &m_arguments;
    }
    
    ~Event();
    
    
private:
    Event();
    
    string m_caller;
    EventHandler* m_target;
    string m_eventName;
    int m_argCount;
    vector<string> m_arguments;
    

    
};


#endif /* defined(__SDLGameEngine__Event__) */
