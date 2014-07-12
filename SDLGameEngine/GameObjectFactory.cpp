//
//  GameObjectFactory.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/15/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::s_Instance = 0;

GameObjectFactory* GameObjectFactory::Instance(){
    if (!s_Instance){
        s_Instance = new GameObjectFactory();
    }
    return s_Instance;
}


bool GameObjectFactory::registerType(string typeID, BaseCreator *pCreator){
    
    map<string,BaseCreator*>::iterator p_tempCreator;
    
    p_tempCreator = m_creators.find(typeID);
    
    if ( p_tempCreator != m_creators.end()){
        delete pCreator;
        return false;
    }
    
    m_creators[typeID] = pCreator;
    
    return true;
}

GameObject* GameObjectFactory::create(string typeID){
    
    map<string,BaseCreator*>::iterator p_tempCreator;
    
    p_tempCreator =  m_creators.find(typeID);
    
    if (p_tempCreator == m_creators.end()){
        cout << "Could not find type!";
        return 0;
    }
    
    BaseCreator* pCreator = (*p_tempCreator).second;    
    return pCreator->createGameObject();
}