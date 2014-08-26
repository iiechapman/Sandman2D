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
#include <string>
#include "EventHandler.h"

using namespace std;

class Event{
public:
    
    Event(string caller, EventHandler* target, string eventName,
          int argCount, vector<string> arguments);
    
    string getCaller();
    EventHandler* getTarget();
    string getEventName();
    int getArgCount();
    vector<string>* getArguments();
    void printOut();
    
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
