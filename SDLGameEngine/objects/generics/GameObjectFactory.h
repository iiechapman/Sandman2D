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
#include "IGameObject.h"

using namespace std;

class IBaseCreator{
public:
    virtual IGameObject* createGameObject() const = 0;
    virtual ~IBaseCreator(){}
};



class GameObjectFactory{
public:
    static GameObjectFactory* Instance();
    
    bool registerType(string typeID, IBaseCreator* pCreator);
    IGameObject* create(string typeID);
    
private:
    map<string, IBaseCreator*> m_creators;
    static GameObjectFactory* s_Instance;
};


#endif /* defined(__SDLGameDevelopmentChapter1__GameObjectFactory__) */






















































//END