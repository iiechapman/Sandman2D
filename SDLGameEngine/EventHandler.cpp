//
//  EventHandler.cpp
//  SDLGameEngine
//
<<<<<<< HEAD
//  Created by Evan Chapman on 8/3/14.
=======
//  Created by Evan Chapman on 8/7/14.
>>>>>>> 01592973136412738e1b3cd3181cef456b96cc90
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "EventHandler.h"

<<<<<<< HEAD

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
=======
EventHandler::EventHandler(){
    cout << "Event Handler created\n";
}


EventHandler* EventHandler::s_pInstance = 0;


EventHandler* EventHandler::Instance(){
    
    
    return 0;
}

>>>>>>> 01592973136412738e1b3cd3181cef456b96cc90
