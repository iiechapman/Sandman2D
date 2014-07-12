//
//  SDLGameObject.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/30/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <string>
#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject()
:GameObject(){
}

SDLGameObject::SDLGameObject(GameObjectParams params)
:GameObject(params){
}

void SDLGameObject::load(GameObjectParams params){
    //cout << "Loading Params\n";
    m_params = params;
}

SDLGameObject::~SDLGameObject(){
    cout << "Deleted SDLGame Object\n";
}

void SDLGameObject::draw(){
    //Old draw method, animate and flip left and right depending on velocity
    if (GetParams().getVelocity().getX() >= 0){
        TextureManager::Instance()->
        drawFrame(&m_params, Game::Instance()->getRenderer(),
                  SDL_FLIP_NONE,Game::Instance()->getZoom());
    } else {
        TextureManager::Instance()->
        drawFrame(&m_params, Game::Instance()->getRenderer(),
                  SDL_FLIP_HORIZONTAL,Game::Instance()->getZoom());
    }
}

void SDLGameObject::update(){
    m_params.getVelocity().setX
    (m_params.getVelocity().getX() + m_params.getAcceleration().getX());
    m_params.getVelocity().setY
    (m_params.getVelocity().getY() + m_params.getAcceleration().getY());
    
    
    m_params.setX(m_params.getX() + m_params.getVelocity().getX());
    m_params.setY(m_params.getY() + m_params.getVelocity().getY());
}

void SDLGameObject::clean(){
    //Perform any cleanup
}

void SDLGameObject::collision(){
    //Handle collision
    cout << "Collision detected\n";
    
}





































































//END