//
//  GameObjectFactory.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/15/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__GameObjectFactory__
#define __SDLGameDevelopmentChapter1__GameObjectFactory__

#include <iostream>
#include <string>
#include <map>
#include "GameObject.h"

using namespace std;

class BaseCreator{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator(){}
};



class GameObjectFactory{
public:
    static GameObjectFactory* Instance();
    
    bool registerType(string typeID, BaseCreator* pCreator);
    GameObject* create(string typeID);
    
private:
    map<string, BaseCreator*> m_creators;
    static GameObjectFactory* s_Instance;
};


#endif /* defined(__SDLGameDevelopmentChapter1__GameObjectFactory__) */
