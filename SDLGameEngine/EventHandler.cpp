//
//  EventHandler.cpp
//  SDLGameEngine
//

//  Created by Evan Chapman on 8/3/14.

//  Created by Evan Chapman on 8/7/14.

//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "EventHandler.h"


EventHandler::EventHandler(){
    cout << "New event handler\n";
}

EventHandler::~EventHandler(){
    //Delete event handler
    //cout << "Deleted event handler\n";
}

void EventHandler::registerHandler(){

}

void EventHandler::deregisterHandler(){

}

void EventHandler::handleEvent(string event){
    //cout << "Handling event " << event << endl;
    m_events.push_back(event);
}