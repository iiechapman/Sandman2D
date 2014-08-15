//
//  EventHandler.cpp
//  SDLGameEngine
//
//  Created by Evan Chapman on 8/3/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "EventHandler.h"
#include "EventManager.h"

EventHandler::EventHandler(){
    cout << "New event handler\n";
}

EventHandler::~EventHandler(){
    //Delete event handler
    //cout << "Deleted event handler\n";
}

void EventHandler::registerHandler(){
    EventManager::Instance()->addHandler(this);
}

void EventHandler::deregisterHandler(){
    EventManager::Instance()->removeHandler(this);
}

void EventHandler::handleEvent(Event* event){
    //cout << "Handling event " << event << endl;
    m_events.push_back(event);
}


//Check if handler handles specific event
bool EventHandler::handlesEvent(string eventName){
    for (int i = 0 ; i < m_registeredEvents.size() ; i++){
        if (m_registeredEvents[i] == eventName){
            return true;
        }
    }
    return false;
}


void EventHandler::registerEvent(string eventName){
    m_registeredEvents.push_back(eventName);
}

void EventHandler::deregisterEvent(string eventName){
    vector<string>::iterator deadValue =
    find(m_registeredEvents.begin(), m_registeredEvents.end(), eventName);
    m_registeredEvents.erase(deadValue);
}