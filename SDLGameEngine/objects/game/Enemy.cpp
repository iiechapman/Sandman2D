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
    //GetParams().setAI(true);
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
    
    //Update AI state
    //TODO Expand AI system
    if (GetParams().aiEnabled()){
        
        int switchState = rand() % 200;
        //AI_State prevState = GetParams().getAIState();
        
        switch (switchState) {
            case 0:
                GetParams().setAIState(MOVE_NONE);
                break;
                
            case 1:
                GetParams().setAIState(MOVE_RIGHT);
                break;
                
            case 2:
                GetParams().setAIState(MOVE_LEFT);
                break;
                
                
            default:

                break;
        }
        
        switch (GetParams().getAIState()) {
            case MOVE_RIGHT:
                GetParams().getAcceleration().setX(1);
                break;
                
            case MOVE_LEFT:
                GetParams().getAcceleration().setX(-1);
                break;
                
                
            default:
                break;
        }
    }
    
    
    //Update position
    Vector2D<double> newPos = GetParams().getPosition();
    Vector2D<double> newYPos = GetParams().getPosition();
    
    newPos.setX(newPos.getX() + GetParams().getAcceleration().getX());
    
    newYPos.setY(newYPos.getY() + GetParams().getHeight());
    newYPos.setX(newYPos.getX() + GetParams().getWidth()/2 * GetParams().getAcceleration().getX());
    
    if (checkCollideWithTile(newPos) || !checkCollideWithTile(newYPos)){
    newPos.setX(newPos.getX() - GetParams().getAcceleration().getX());
        
        switch (GetParams().getAIState()) {
            case MOVE_RIGHT:
                GetParams().setAIState(MOVE_LEFT);
                break;
                
            case MOVE_LEFT:
                GetParams().setAIState(MOVE_RIGHT);
                break;
                
                
            default:
                break;
        }
    }
    
    //Set new position
    GetParams().getPosition().setX(newPos.getX());
    
    //Update animation
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






















































//END