//
//  EventManager.cpp
//  SDLGameEngine
//
//  Created by Evan Chapman on 8/3/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "EventManager.h"


EventManager* EventManager::s_pInstance = 0;


EventManager::EventManager(){
    cout << "New event handler\n";
}

void EventManager::handleEvent
(vector<EventHandler*> targets,string event, int argCount , vector<string> arguments){
    //Send event to all targets
    for (int i = 0 ; i < targets.size(); i++){
        targets[i]->handleEvent(event);
        }
    }




void EventManager::receiveEvent(vector<EventHandler*> targets,string event, int argCount , vector<string> arguments){
    handleEvent(targets, event, argCount, arguments);
}


void EventManager::addHandler(EventHandler *handler){
    m_Handlers.push_back(handler);
}

void EventManager::removeHandler(EventHandler *handler){
    //remove handler here
}