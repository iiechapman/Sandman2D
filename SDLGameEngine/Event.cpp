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


string Event::getCaller(){
    return m_caller;
}

EventHandler* Event::getTarget(){
    return m_target;
}

string Event::getEventName(){
    return m_eventName;
}

int Event::getArgCount(){
    return m_argCount;
}

vector<string>* Event::getArguments(){
    return &m_arguments;
}

void Event::printOut(){
    cout << "Event--" << endl;
    cout << "Name: " << m_eventName << endl;
    cout << "Caller: " << m_caller << endl;
    cout << "Target: " << m_target << endl;
    cout << "ArgC: " << m_argCount << endl;
}








































































//END