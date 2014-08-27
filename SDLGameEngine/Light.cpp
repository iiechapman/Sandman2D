//
//  Light.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Light.h"
#include "Game.h"

Light::Light(){
    //cout << "Created new Light\n";
    m_params.setType("Light");
}

Light::Light(GameObjectParams params , int numberFrames)
:SDLGameObject(params){
    GetParams().setMaxFrames(numberFrames);
}

void Light::load(GameObjectParams params){
    SDLGameObject::load(params);
}

void Light::draw(){
    SDLGameObject::draw();
    //cout << "x: " << GetParams().getX() << endl;
}

void Light::collision(){
    //Need to remove collision from this class
}

void Light::update(){
    
    GetParams().setFrame(0);

    //TODO Add LockTo to SDLGameObject, allowing any object to lock to another
    //If the light has a lock, position it to the object
    if (GetParams().getLockTo() == string("player")){

        GetParams().setX
        (Game::Instance()->getPlayer()->GetParams().getX()
         + Game::Instance()->getPlayer()->GetParams().getWidth()/2
         - GetParams().getWidth()/2);
        
        GetParams().setY
        (Game::Instance()->getPlayer()->GetParams().getY()
         + Game::Instance()->getPlayer()->GetParams().getHeight()/2
         - GetParams().getHeight()/2);
    
    }
    
    
    SDLGameObject::update();
}

void Light::clean(){
    SDLGameObject::clean();
    cout << "Cleaning Light\n";
}