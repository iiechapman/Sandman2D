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

class Event;

using namespace std;

class EventHandler{
public:
    EventHandler();
    ~EventHandler();
    
    void handleEvent(Event* event);
    
    bool hasEvents();
    
    void registerHandler();
    void deregisterHandler();
    
    void registerEvent(string eventName);
    void deregisterEvent(string eventName);
    
    bool handlesEvent(string eventName);
    
    unsigned long getSize();
    
    Event* getTopEvent();
    
private:
    vector<Event*> m_events;
    vector<string> m_registeredEvents;
};

#endif /* defined(__SDLGameEngine__EventHandler__) */
