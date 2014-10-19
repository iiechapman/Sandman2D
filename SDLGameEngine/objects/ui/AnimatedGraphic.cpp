//
//  AnimatedGraphic.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "AnimatedGraphic.h"
#include "InputHandler.h"

AnimatedGraphic::AnimatedGraphic(){
    //cout << "Created new animated graphic\n";
}

AnimatedGraphic::AnimatedGraphic
(GameObjectParams params , int totalFrames, int animSpeed):
SDLGameObject(params)
{
    GetParams().setMaxFrames(totalFrames);
}

void AnimatedGraphic::load(GameObjectParams params){
    SDLGameObject::load(params);
}

void AnimatedGraphic::draw(){
    SDLGameObject::draw();
}

void AnimatedGraphic::update(){
    
    GetParams().setFrame
    (int((SDL_GetTicks()/ (1000 / GetParams().getAnimSpeed())) % GetParams().getTotalFrames()));

    
    SDLGameObject::update();
}

void AnimatedGraphic::clean(){
    SDLGameObject::clean();
    cout << "Cleaning AnimatedGraphic\n";
}

void AnimatedGraphic::collision(){
    
}






















































//END