//
//  EventHandler.h
//  SDLGameEngine
//

//  Created by Evan Chapman on 8/3/14.

//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameEngine__EventHandler__
#define __SDLGameEngine__EventHandler__

#include <iostream>
#include <vector>
#include <map>

class Event;

using namespace std;

class EventHandler{
public:
    EventHandler();
    ~EventHandler();
    
    void handleEvent(string event);
    
    void registerHandler();
    void deregisterHandler();
    
    unsigned long getSize(){
        return m_events.size();
    }
    
    string getTopEvent(){
        string topEvent = m_events.back();
        m_events.pop_back();
        return topEvent;
    }
    
private:
    vector<string> m_events;
};

#endif /* defined(__SDLGameEngine__EventHandler__) */
