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
    if (GetParams().getVelocity().getX() != 0 && GetParams().getVelocity().getY() == 0){
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
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z)) {
        if (!m_bJumpHeld && m_numJumps > 0 && m_bCanJump){
            m_bIsJumping = true;
            m_numJumps--;
        }
        m_bJumpHeld = true;
    } else {
        m_bJumpHeld = false;
    }
    
}

void Player::handlePhysics(){
    
    //Switch direction according to movement
    if (m_bMoveRight){
        GetParams().setRight(true);
        GetParams().setLeft(false);
    }
    
    if (m_bMoveLeft){
        GetParams().setRight(false);
        GetParams().setLeft(true);
    }
    
    
    //Move right
    if (m_bMoveRight){
        GetParams().getAcceleration().setX(m_horizontalSpeed);
        
    } else if (GetParams().getVelocity().getX() > 0) {
        //If not moving right, slow down to stop
        GetParams().getAcceleration().setX(-m_horizontalDrag*2);
        
        //Stop at 0 movement
        if (GetParams().getVelocity().getX() <= m_horizontalDrag*2 ){
            GetParams().getVelocity().setX(0);
            GetParams().getAcceleration().setX(0);
        }
    }
    
    //Move Left
    if (m_bMoveLeft){
        GetParams().getAcceleration().setX(-m_horizontalSpeed);
        
    } else if (GetParams().getVelocity().getX() < 0) {
        //If not moving left, slow down to stop
        GetParams().getAcceleration().setX(m_horizontalDrag*2);
        
        //Stop at 0 movement
        if (GetParams().getVelocity().getX() >= m_horizontalDrag*2 ){
            GetParams().getVelocity().setX(0);
            GetParams().getAcceleration().setX(0);
        }
    }
    
    //Jumping
    if (m_bIsJumping){
        GetParams().getVelocity().setY(-(m_jumpSpeed));
        m_bIsJumping = false;
    }
    
    
    //Jetting
    if (m_bIsJetting && !(GetParams().getVelocity().getY()==0) && m_currentFuel > m_fuelCost){
        m_currentFuel -= m_fuelCost;
        m_currentGravity = m_jetGravity;
        GetParams().getVelocity().setY(GetParams().getVelocity().getY()-m_jetSpeed);
        
        if (m_bMoveRight){
            GetParams().setAngle(20);
        } else if (m_bMoveLeft){
            GetParams().setAngle(-20);
        } else {
            GetParams().setAngle(0);
        }
        
    } else {
        if (m_numJumps>0){
            GetParams().setAngle(0);
        }
        m_currentGravity = m_normalGravity;
        m_bIsJetting = false;
    }
    
    
    //Handle Spinning
    if (m_bIsFalling && m_numJumps == 0 && !m_bIsJetting){
        
        if (GetParams().dirLeft()){
            GetParams().setAngle(GetParams().getAngle() - (GetParams().getVelocity().getY()) - 20);
            
        } else if (GetParams().dirRight()){
            GetParams().setAngle(GetParams().getAngle() + (GetParams().getVelocity().getY()) + 20);
        }
    
    }

    
    
    //Handle gravity
    if (m_bIsFalling){
        if (GetParams().getVelocity().getY() < 1){
            GetParams().getAcceleration().setY(m_normalGravity);
            
            if (m_bIsJetting && GetParams().getVelocity().getY() > 0 ){
                GetParams().getVelocity().setY(0);
            }
        }
    }
}

void Player::handleMovement(){
    
    //Check X movement and collision
    Vector2D newPos = GetParams().getPosition();
    newPos.setX(newPos.getX() + GetParams().getVelocity().getX() + GetParams().getAcceleration().getX());
    
    //Check X collision
    if (checkCollideTile(newPos)){
        GetParams().getVelocity().setX(0);
        GetParams().getAcceleration().setX(0);
    }
    
    
    //Check Y Movement and Collision
    newPos = GetParams().getPosition();
    newPos.setY(newPos.getY() + GetParams().getVelocity().getY() + GetParams().getAcceleration().getY());
    //newPos.setY(newPos.getY());
    
    //Check Y collision
    if (checkCollideTile(newPos)){
        //When hitting the ground
        if (m_bIsFalling && GetParams().getVelocity().getY() > 0) {
            m_bCanJump = true;
            m_bIsOnGround = true;
            m_numJumps = m_maxJumps;
            m_currentFuel = m_maxFuel;
            GetParams().setAngle(0);
        }
        
        m_bIsFalling = false;
        
        GetParams().getVelocity().setY(0);
        GetParams().getAcceleration().setY(0);
    } else {
        m_bIsFalling = true;
        m_bIsOnGround = false;
    }

    
    //Alter position based on velocity and acceleration
    GetParams().getVelocity().setX
    (GetParams().getVelocity().getX() + GetParams().getAcceleration().getX());
    
    GetParams().getVelocity().setY
    (GetParams().getVelocity().getY() + GetParams().getAcceleration().getY());
    
    
    GetParams().setX(GetParams().getX() + GetParams().getVelocity().getX());
    GetParams().setY(GetParams().getY() + GetParams().getVelocity().getY());
    
    //Check intersection and fix
    
    //Check X intersection after move
    newPos = GetParams().getPosition();
    //Check X collision
    if (checkCollideTile(newPos)){
        cout << "X Intersect!\n";
        GetParams().setX(GetParams().getX() - GetParams().getVelocity().getX());
        GetParams().getVelocity().setX(0);
        GetParams().getAcceleration().setX(0);
    }
    
    
    //Check Y intersection after move
    newPos = GetParams().getPosition();
    //Check Y collision
    if (checkCollideTile(newPos)){
        cout << "Y Intersect\n";
        GetParams().setY(GetParams().getY() - GetParams().getVelocity().getY());
        GetParams().getVelocity().setY(0);
        GetParams().getAcceleration().setY(0);
    }
    
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
        (pos.getX() + GetParams().getWidth() - GetParams().getWidth()/4,
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








