//
//  EventHandler.cpp
//  SDLGameEngine
//
//  Created by Evan Chapman on 8/3/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "EventHandler.h"


EventHandler* EventHandler::s_pInstance = 0;

EventHandler* EventHandler::Instance(){
    if (!s_pInstance){
        s_pInstance = new EventHandler();
    }
    return s_pInstance;
}


EventHandler::EventHandler(){
    cout << "New event handler\n";
}