//
//  Player.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Player.h"
#include "InputHandler.h"


Player::Player(){
    cout << "Created player object\n";
    m_params.setType("Player");
}

Player::Player(GameObjectParams params , int numberFrames)
:SDLGameObject(params){
    GetParams().setMaxFrames(numberFrames);


}

void Player::load(GameObjectParams params){
    SDLGameObject::load(params);
}

void Player::draw(){
    SDLGameObject::draw();
}

void Player::collision(){
    m_params.setX(m_params.getX() - m_params.getVelocity().getX());
    m_params.setY(m_params.getY() - m_params.getVelocity().getY());
    
    m_params.getVelocity().setX(0);
    m_params.getVelocity().setY(0);
    
    m_params.getAcceleration().setX(0);
    m_params.getAcceleration().setY(0);
    
}

void Player::update(){
    handleInput();
    handlePhysics();
    handleAnimation();
    SDLGameObject::update();
}

void Player::handleAnimation(){
    //Update animation
    if (GetParams().getVelocity().getX() != 0){
        GetParams().setFrame
        (int((SDL_GetTicks()/ (1000 / GetParams().getAnimSpeed())) % GetParams().getTotalFrames()));
    } else {
        GetParams().setFrame(0);
    }
}

void Player::handleInput(){
    //Mouse control
    if (InputHandler::Instance()->getMouseButtonState(RIGHT)){
        Vector2D* vec = InputHandler::Instance()->getMousePosition();
        
        GetParams().setVelocity((*vec - GetParams().getPosition()) / 50 );
        
        //Keyboard control
    } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)){
        GetParams().getAcceleration().setY(-.1);
    } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)){
        GetParams().getAcceleration().setX(.5);
    } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)){
        GetParams().getAcceleration().setX(-.5);
    } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)){
        GetParams().getAcceleration().setY(-.5);
    } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)){
        GetParams().getAcceleration().setY(.5);
    } else {
        GetParams().getAcceleration().setX(0);
        GetParams().getAcceleration().setY(0);
        
        //cout << "Current XVel: " << GetParams().getVelocity().getX() << endl;
        if (GetParams().getVelocity().getX() > 0){
            GetParams().getVelocity().setX(GetParams().getVelocity().getX() - .1);
            //cout << "Slowing down right movement\n";
            if (GetParams().getVelocity().getX() <= 0){
                GetParams().getVelocity().setX(0);
            }
        }
        
        if (GetParams().getVelocity().getX() < 0){
            GetParams().getVelocity().setX(GetParams().getVelocity().getX() + .1);
            //cout << "Slowing down left movement\n";
            if (GetParams().getVelocity().getX() >= 0){
                GetParams().getVelocity().setX(0);
            }
        }
    }
}

void Player::handlePhysics(){
    
    //Handle gravity
    if (GetParams().getVelocity().getY() < 3){
        GetParams().getVelocity().setY(GetParams().getVelocity().getY() + .2);
    }
    
}

void Player::clean(){
    SDLGameObject::clean();
    cout << "Cleaning player\n";
}








