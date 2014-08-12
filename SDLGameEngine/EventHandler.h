//
//  EventHandler.h
//  SDLGameEngine
//
<<<<<<< HEAD
//  Created by Evan Chapman on 8/3/14.
=======
//  Created by Evan Chapman on 8/7/14.
>>>>>>> 01592973136412738e1b3cd3181cef456b96cc90
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameEngine__EventHandler__
#define __SDLGameEngine__EventHandler__

#include <iostream>
#include <vector>
<<<<<<< HEAD
#include "GameObject.h"

using namespace std;

class EventHandler{
public:
    static EventHandler* Instance();
    ~EventHandler();
    
    void HandleEvent(string event);
    
private:
    EventHandler();
    static EventHandler* s_pInstance;
    
    vector<GameObject*> m_eventResponders;
=======
#include <map>
#include "GameObject.h"
using namespace std;


class EventHandler{
public:
    EventHandler* Instance();

    
    void HandleEvents();
    void ReceiveEvent(int argCount , vector<string> arguments);
    
    ~EventHandler();
private:
    EventHandler();
    
    static EventHandler* s_pInstance;
    
    vector<GameObject*> m_Listeners;
>>>>>>> 01592973136412738e1b3cd3181cef456b96cc90
    
};



<<<<<<< HEAD
=======

>>>>>>> 01592973136412738e1b3cd3181cef456b96cc90
#endif /* defined(__SDLGameEngine__EventHandler__) */
