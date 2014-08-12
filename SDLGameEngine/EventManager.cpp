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

void EventManager::handleEvent(string target,string event, int argCount , vector<string> arguments){
    //Send event to all listeners
    for (int i = 0 ; i < m_Handlers.size(); i++){
        if (m_Handlers[i]->isTarget(target)){
            if (m_Handlers[i]->respondsToEvent(event)){
                m_Handlers[i]->handleEvent(event,argCount, arguments);
            }
        }
    }
}



void EventManager::receiveEvent(string target,string event, int argCount , vector<string> arguments){
    handleEvent(target, event, argCount, arguments);
}
