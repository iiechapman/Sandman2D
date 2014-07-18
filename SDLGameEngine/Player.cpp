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

void Player::update(){
    handleInput();
    handlePhysics();
    handleMovement();
    handleAnimation();
    
    SDLGameObject::update();
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
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) ? m_bMoveLeft = true : m_bMoveLeft = false;
    
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) ? m_bIsJetting = true : m_bIsJetting = false;
    
    (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && m_bCanJump) ? m_bIsJumping = true : m_bIsJumping = false;
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)){
        //cout << "Pressed jump\n";
    }
    
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
    
    if (m_bMoveRight){
        GetParams().getAcceleration().setX(m_horizontalSpeed);
        
    } else if (GetParams().getVelocity().getX() > 0) {
        //If not moving right, slow down to stop
        GetParams().getAcceleration().setX(-m_horizontalDrag);
        
        //Stop at 0 movement
        if (GetParams().getVelocity().getX() <= m_horizontalDrag ){
            GetParams().getVelocity().setX(0);
            GetParams().getAcceleration().setX(0);
        }
    }
    
    //Switch flipping according to movement
    if (m_bMoveRight){
        GetParams().setRight(true);
        GetParams().setLeft(false);
    }
    
    if (m_bMoveLeft){
        GetParams().setRight(false);
        GetParams().setLeft(true);
    }
    
    
    
    if (m_bMoveLeft){
        GetParams().getAcceleration().setX(-m_horizontalSpeed);
        
    } else if (GetParams().getVelocity().getX() < 0) {
        //If not moving left, slow down to stop
        GetParams().getAcceleration().setX(m_horizontalDrag);
        
        //Stop at 0 movement
        if (GetParams().getVelocity().getX() >= m_horizontalDrag ){
            GetParams().getVelocity().setX(0);
            GetParams().getAcceleration().setX(0);
        }
    }
    
    if (m_bIsJumping){
        GetParams().getVelocity().setY(-m_jumpSpeed);
        m_bCanJump = false;
    }
    
    if (m_bIsJetting){
        GetParams().getAcceleration().setY(-m_jetSpeed);
        m_bIsFalling = false;
    }
    
    //Handle gravity
    if (m_bIsFalling){
        if (GetParams().getVelocity().getY() < 3){
            GetParams().getAcceleration().setY(m_verticalGravity);
        }
    }
}

void Player::handleMovement(){
    
    //Check X movement and collision
    Vector2D newPos = GetParams().getPosition();
    newPos.setX(newPos.getX() + GetParams().getVelocity().getX() + GetParams().getAcceleration().getX());
    
    if (checkCollideTile(newPos)){
        GetParams().getVelocity().setX(0);
        GetParams().getAcceleration().setX(0);
    }
    
    
    //Check Y Movement and Collision
    newPos = GetParams().getPosition();
    newPos.setY(newPos.getY() + GetParams().getVelocity().getY() + GetParams().getAcceleration().getY());
    newPos.setY(newPos.getY());
    
    if (checkCollideTile(newPos)){
        m_bIsFalling = false;
        
        if (m_bIsFalling) {
            m_bCanJump = true;
        }
        
        GetParams().getVelocity().setY(0);
        GetParams().getAcceleration().setY(0);
    } else {
        m_bIsFalling = true;
    }
    
    
    //Check if no tile below player to make them fall
    if (!m_bIsFalling){
        newPos = GetParams().getPosition();
        newPos.setY(newPos.getY() + 1);
        
        if (!checkCollideTile(newPos)){
            m_bIsFalling = true;
        } else {
            GetParams().getVelocity().setY(0);
            GetParams().getAcceleration().setY(0);
            
            m_bIsFalling = false;
            m_bCanJump = true;
        }
    }
    
    
    GetParams().getVelocity().setX
    (GetParams().getVelocity().getX() + GetParams().getAcceleration().getX());
    
    GetParams().getVelocity().setY
    (GetParams().getVelocity().getY() + GetParams().getAcceleration().getY());
    
    
    GetParams().setX(GetParams().getX() + GetParams().getVelocity().getX());
    GetParams().setY(GetParams().getY() + GetParams().getVelocity().getY());
    
}

bool Player::checkCollideTile(Vector2D pos){
    
    //Iterate through all collision layers
    for (vector<TileLayer*>::const_iterator it = m_pCollisionLayers.begin();
         it != m_pCollisionLayers.end() ; it++){
        
        TileLayer* pTileLayer = (*it);
        vector<vector<int>> tiles = pTileLayer->getTileIDs();
        
        //Get layers position
        //Vector2D layerPos = pTileLayer->getPosition();
        Vector2D layerPos
        (pTileLayer->getPosition().getX(),
         pTileLayer->getPosition().getY());
        
        int x,y,tileColumn,tileRow,tileID = 0;
        
        //Calculate position on tile map
        x = ((layerPos.getX()) / pTileLayer->getTileSize());
        y = ((layerPos.getY()) / pTileLayer->getTileSize());
        
        //New collision detection
        Vector2D startPos = pos;
        
        startPos.setX(startPos.getX() + GetParams().getWidth()/4);
        startPos.setY(startPos.getY() + GetParams().getHeight()/4);
        
        Vector2D endPos
        (pos.getX() + GetParams().getWidth()- GetParams().getWidth()/4,
         pos.getY() + GetParams().getHeight());
        
        
        for (int i = startPos.getX(); i < endPos.getX(); i++ ){
            for (int j = startPos.getY() ; j < endPos.getY() ; j++){
                tileColumn = i / pTileLayer->getTileSize();
                tileRow = j / pTileLayer->getTileSize();
                
                if (tileColumn + x >= Game::Instance()->getMapWidth() / pTileLayer->getTileSize() ||
                    tileColumn + x < 0){
                    tileID = 0;
                } else if (tileRow + y >= (Game::Instance()->getMapHeight() / pTileLayer->getTileSize()) ||
                           tileRow + y < 0){
                    tileID = 0;
                } else {
                    tileID = tiles[tileRow + y][tileColumn + x];
                }
                
                //If tileID is not blank, collision occured
                if (tileID != 0 ){
                    return true;
                }
            }
        }
    }
    return false;
}


void Player::clean(){
    SDLGameObject::clean();
    cout << "Cleaning player\n";
}








