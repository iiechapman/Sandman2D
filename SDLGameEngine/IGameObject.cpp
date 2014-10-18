//
//  GameObject.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "IGameObject.h"

IGameObject::IGameObject(){
}

IGameObject::IGameObject(GameObjectParams params){
    m_params = params;
}

IGameObject::~IGameObject(){
    //cout << "Deleted game object\n";
}

GameObjectParams& IGameObject::GetParams(){
    return m_params;
}

void IGameObject::clean(){
    cout << "Cleaning game object\n";
}