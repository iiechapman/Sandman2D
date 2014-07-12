//
//  Light.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Light.h"
#include "InputHandler.h"
#include "Game.h"

Light::Light(){
    cout << "Created new Light\n";
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
    cout << "x: " << GetParams().getX() << endl;
}

void Light::collision(){
    
}

void Light::update(){
    
    GetParams().setFrame(0);
   // GetParams().setVelocity({-1,0});
    if (GetParams().getLockTo() == string("player")){
        GetParams().setScrolling(false);
        GetParams().setX
        (Game::Instance()->getPlayer()->GetParams().getX() - GetParams().getWidth()/2);
        
        GetParams().setY
        (Game::Instance()->getPlayer()->GetParams().getY() - GetParams().getHeight()/2);
        
        GetParams().setVelocity(Game::Instance()->getPlayer()->GetParams().getVelocity());
    }
    
    
    SDLGameObject::update();
}

void Light::clean(){
    SDLGameObject::clean();
    cout << "Cleaning Light\n";
}