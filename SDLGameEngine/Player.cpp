//
//  Player.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Player.h"
#include "InputHandler.h"
#include "Game.h"


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
    //m_params.setX(m_params.getX() - m_params.getVelocity().getX());
    m_params.setY(m_params.getY() - m_params.getVelocity().getY());
    
    //m_params.getVelocity().setX(0);
    m_params.getVelocity().setY(0);
    
    //m_params.getAcceleration().setX(0);
    m_params.getAcceleration().setY(0);
    m_bIsFalling = false;
}

void Player::update(){
    m_bIsFalling = true;
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
    
    //Hold shift to run
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LSHIFT)){
        m_horizontalSpeed = m_runSpeed;
    } else {
        m_horizontalSpeed = m_walkSpeed;
    }
    
    //New Keyboard control
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) ? m_bMoveRight = true : m_bMoveRight = false;
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) ? m_bMoveRight = true : m_bMoveRight = false;
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) ? m_bMoveRight = true : m_bMoveRight = false;
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) ? m_bMoveRight = true : m_bMoveRight = false;
    
//Old control code
    
//    
//    //Mouse control
//    if (InputHandler::Instance()->getMouseButtonState(RIGHT)){
//        Vector2D* vec = InputHandler::Instance()->getMousePosition();
//        
//        GetParams().setVelocity((*vec - GetParams().getPosition()) / 50 );
//        
//        //Keyboard control
//    } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)){
//        GetParams().getVelocity().setX(m_horizontalSpeed);
//    } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)){
//        GetParams().getVelocity().setX(-m_horizontalSpeed);
//        
//        //Press space for jump, up for jetpack
//    } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)){
//        GetParams().getAcceleration().setY(-m_jumpSpeed);
//        GetParams().getVelocity().setY(-m_jumpSpeed);
//    } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)){
//        GetParams().getAcceleration().setY(-m_jetSpeed);
//        
//    } else {
//        
//        
//        GetParams().getAcceleration().setX(0);
//        GetParams().getAcceleration().setY(0);
//        
//        //cout << "Current XVel: " << GetParams().getVelocity().getX() << endl;
//        if (GetParams().getVelocity().getX() > 0){
//            GetParams().getVelocity().setX
//            (GetParams().getVelocity().getX() - m_horizontalDrag);
//            //cout << "Slowing down right movement\n";
//            if (GetParams().getVelocity().getX() <= 0){
//                GetParams().getVelocity().setX(0);
//            }
//        }
//        
//        if (GetParams().getVelocity().getX() < 0){
//            GetParams().getVelocity().setX
//            (GetParams().getVelocity().getX() + m_horizontalDrag);
//            //cout << "Slowing down left movement\n";
//            if (GetParams().getVelocity().getX() >= 0){
//                GetParams().getVelocity().setX(0);
//            }
//        }
//    }
    
}

void Player::handlePhysics(){
    
    //Handle gravity
    if (m_bIsFalling){
        if (GetParams().getVelocity().getY() < 3){
            GetParams().getVelocity().setY
            (GetParams().getVelocity().getY() + m_verticalGravity);
        }
    }
    
}

void Player::clean(){
    SDLGameObject::clean();
    cout << "Cleaning player\n";
}








