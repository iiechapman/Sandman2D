//
//  GameObject.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject(){
}

GameObject::GameObject(GameObjectParams params){
    m_params = params;
}

GameObject::~GameObject(){
    //cout << "Deleted game object\n";
}

GameObjectParams& GameObject::GetParams(){
    return m_params;
}

void GameObject::clean(){
    cout << "Cleaning game object\n";
}