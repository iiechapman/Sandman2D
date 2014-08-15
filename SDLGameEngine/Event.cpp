//
//  Event.cpp
//  SDLGameEngine
//
//  Created by Evan Chapman on 8/14/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Event.h"


Event::Event(string caller, EventHandler* target, string eventName,
             int argCount, vector<string> arguments):
m_caller(caller), m_target(target), m_eventName(eventName), m_argCount(argCount),
m_arguments(arguments)
{
    //Created new event object
}


Event::~Event(){
    //deleted object
}