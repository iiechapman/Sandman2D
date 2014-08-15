//
//  Enemy.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Enemy.h"
#include "InputHandler.h"

Enemy::Enemy(){
    //cout << "Created new enemy\n";
    //m_params = new GameObjectParams();
    m_params.setType("Enemy");
}

Enemy::Enemy(GameObjectParams params , int numberFrames)
:SDLGameObject(params){
    GetParams().setVelocity({0,0});
    GetParams().setMaxFrames(numberFrames);
}

void Enemy::load(GameObjectParams params){
    SDLGameObject::load(params);
}

void Enemy::collision(){
    
}

void Enemy::draw(){
    SDLGameObject::draw();
}

void Enemy::update(){
    //cout << "Total Frames: " << GetParams().getTotalFrames() << " Speed: " << GetParams().getAnimSpeed() << endl;
    
    //Check events
    while (GetParams().getEvents()->getSize() > 0) {
        Event* event = GetParams().getEvents()->getTopEvent();
        cout << "Checking event " << event->getEventName() << endl;
        //Collect event moves object away
        if (event->getEventName() == string("collect")){
            GetParams().getPosition().setX(-99999);
        }
        
    }
    
    
    if (GetParams().getTotalFrames()>0 && GetParams().getAnimSpeed()>0){
        GetParams().setFrame
        (GetParams().getStartFrame() +(int((SDL_GetTicks()/ ((1000 / GetParams().getAnimSpeed())) % GetParams().getTotalFrames()))));
    } else {
        GetParams().setFrame(0);
    }
    
    SDLGameObject::update();
}

void Enemy::clean(){
    SDLGameObject::clean();
    cout << "Cleaning Enemy\n";
}
