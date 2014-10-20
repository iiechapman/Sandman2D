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
(vector<EventHandler*> targets,Event* event, int argCount , vector<string> arguments){
    
    //If event is targeted, send to targets
    if (targets.size() >0){
    //Send event to all targets
    for (int i = 0 ; i < targets.size(); i++){
        cout << "Targeting message\n";
        //Pass event to intended target
        targets[i]->handleEvent(event);
        }
    } else {
        //Else broadcast to all listeners
        for (int i = 0 ; i < m_Handlers.size(); i++) {
            //check if handler registered event
            if (m_Handlers[i]->handlesEvent(event->getEventName())){
                //handle event
                m_Handlers[i]->handleEvent(event);
            }
        }
    }
    
}

void EventManager::handleEvent(vector<Event*>* events){
    for (int i = 0 ; i < events->size() ; i++){
        //cout << "Num of Events: " << events->size() << "\n";
        //cout << "Handling #" << i << " ";
        //(*events)[i]->printOut();
        
        //Send targeted message
        if ((*events)[i]->getTarget()){
            //cout << "Targeted message\n";
            (*events)[i]->getTarget()->handleEvent((*events)[i]);
            
        } else {
            //broadcast message
            //cout << "Broadcast message\n";
            bool foundResponder = false;
            for (int j = 0 ; j < m_Handlers.size() ; j++){
                if (m_Handlers[j]->handlesEvent((*events)[i]->getEventName())){
                    //handle event
                    //cout << "Found registered event handler!\n";
                    m_Handlers[j]->handleEvent((*events)[i]);
                    foundResponder = true;
                }
                if (!foundResponder){
                    cout << "No handler for: \"" << (*events)[i]->getEventName() << "\"\n";
                }
            }
        }
    }
}

void EventManager::receiveEvent(vector<Event*> *events){
    handleEvent(events);
}

void EventManager::receiveEvent(vector<EventHandler*> targets,Event* event, int argCount , vector<string> arguments){
    handleEvent(targets, event, argCount, arguments);
}


void EventManager::addHandler(EventHandler *handler){
    m_Handlers.push_back(handler);
}

void EventManager::removeHandler(EventHandler *handler){
    //remove handler here
}






















































//END