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
    
    void handleEvent(Event* event);
    
    bool hasEvents(){
        return (m_events.size()>0);
    }
    
    void registerHandler();
    void deregisterHandler();
    
    void registerEvent(string eventName);
    void deregisterEvent(string eventName);
    
    bool handlesEvent(string eventName);
    
    unsigned long getSize(){
        return m_events.size();
    }
    Event* getTopEvent(){
        Event* topEvent = m_events.back();
        m_events.pop_back();
        return topEvent;
    }
    
private:
    vector<Event*> m_events;
    vector<string> m_registeredEvents;
};

#endif /* defined(__SDLGameEngine__EventHandler__) */
