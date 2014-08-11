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
#include "SoundManager.h"


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
    //InputHandler::Instance()->printJoyStats(0);
    //New Keyboard/Gamepad control
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) ||
        InputHandler::Instance()->getButtonState(0, XB_DPAD_RIGHT)){
        m_bMoveRight = true;
    } else {
        m_bMoveRight = false;
    }
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) ||
        InputHandler::Instance()->getButtonState(0, XB_DPAD_LEFT)){
        m_bMoveLeft = true;
    } else {
        m_bMoveLeft = false;
    }
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) ||
        InputHandler::Instance()->getButtonState(0, XB_DPAD_UP)){
        m_bIsJetting = true;
        SoundManager::Instance()->playSound("jet_sound");
    } else {
        m_bIsJetting = false;
    }
    
    if ((InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) ||
         InputHandler::Instance()->getButtonState(0, XB_DPAD_DOWN)) &&
        m_bIsStomping == false){
        SoundManager::Instance()->playSound("stomp_sound");
        m_bIsStomping = true;
    }
    
    
    //Jump Button
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_X) ||
        InputHandler::Instance()->getButtonState(0, XB_A_BUTTON)){
        if (!m_bJumpHeld && m_numJumps > 0 && !m_bUsedDoubleJump){
            m_bIsJumping = true;
            m_numJumps--;
            SoundManager::Instance()->playSound("jump_sound");
        }
        m_bJumpHeld = true;
    } else {
        m_bJumpHeld = false;
    }
    
    
    //Slide Button
    if ((InputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z) ||
         InputHandler::Instance()->getButtonState(0, XB_B_BUTTON) )
        && !m_bIsBoosting && !m_bIsStomping && !m_bBoostHeld){
        m_BoostTimer = m_BoostTime;
        m_bIsBoosting = true;
        m_bBoostHeld = true;
        SoundManager::Instance()->playSound("boost_sound");
    }
    
    if (!(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z) ||
         InputHandler::Instance()->getButtonState(0, XB_B_BUTTON))) {
        if (m_BoostTimer <= 0){
            m_bBoostHeld = false;
        }
    }
    
    //Ghost mode
    if ((InputHandler::Instance()->isKeyDown(SDL_SCANCODE_T) ||
         InputHandler::Instance()->getButtonState(0, XB_L1_BUTTON))){
        m_bCheckCollision = false;
    } else {
        m_bCheckCollision = true;
    }
    
    //Fly mode
    if ((InputHandler::Instance()->isKeyDown(SDL_SCANCODE_Y) ||
         InputHandler::Instance()->getButtonState(0, XB_R1_BUTTON))){
        GetParams().setY(GetParams().getY()-10);
        GetParams().getAcceleration().setY(0);
    }
}

void Player::handlePhysics(){
    
    //Switch direction according to movement
    if (m_bMoveRight){
        if (!m_bWallCling){
            GetParams().setRight(true);
            GetParams().setLeft(false);
        } else {
            //If clinging to wall, flip direction
            GetParams().setRight(false);
            GetParams().setLeft(true);
        }
    }
    
    if (m_bMoveLeft){
        if (!m_bWallCling){
            GetParams().setRight(false);
            GetParams().setLeft(true);
        } else {
            GetParams().setRight(true);
            GetParams().setLeft(false);
        }
    }
    
    
    //Move right
    if (m_bMoveRight){
        GetParams().getAcceleration().setX(m_horizontalSpeed);
        
    } else if (m_bMoveLeft){
        //Move Left
        GetParams().getAcceleration().setX(-m_horizontalSpeed);
    } else {
        
        if (GetParams().getVelocity().getX() < 0) {
            //If not moving left, slow down to stop
            GetParams().getAcceleration().setX(m_horizontalDrag*4);
            //Stop at 0 movement
            if (GetParams().getVelocity().getX() >= -(m_horizontalDrag*4)){
                GetParams().getVelocity().setX(0);
                GetParams().getAcceleration().setX(0);
            }
            
        }
        
        if (GetParams().getVelocity().getX() > 0) {
            //If not moving right, slow down to stop
            GetParams().getAcceleration().setX(-(m_horizontalDrag*4));
            
            //Stop at 0 movement
            if (GetParams().getVelocity().getX() <= m_horizontalDrag*4){
                GetParams().getVelocity().setX(0);
                GetParams().getAcceleration().setX(0);
            }
        }
        
    }
    
    
    //Jumping
    if (m_bIsJumping){
        GetParams().getVelocity().setY(-(m_jumpSpeed));
        m_bIsJumping = false;
        
        if (m_bWallCling){
            if (GetParams().dirRight()){
                GetParams().getVelocity().setX((m_jumpSpeed*2));
                
            } else if (GetParams().dirLeft()){
                GetParams().getVelocity().setX(-(m_jumpSpeed*2));
            }
        }
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
        if (m_numJumps>0 && !m_bIsBoosting){
            GetParams().setAngle(0);
        }
        m_currentGravity = m_normalGravity;
        m_bIsJetting = false;
    }
    
    //Handle Spinning
    if (m_bIsFalling && m_numJumps == 0 && !m_bIsJetting && !m_bIsStomping){
        
        if (GetParams().dirLeft()){
            GetParams().setAngle(GetParams().getAngle() - (GetParams().getVelocity().getY()) - 30);
            
        } else if (GetParams().dirRight()){
            GetParams().setAngle(GetParams().getAngle() + (GetParams().getVelocity().getY()) + 30);
        }
        
    }
    
    
    
    //Handle gravity
    if (m_bIsFalling){
        if (GetParams().getVelocity().getY() < 1){
            GetParams().getAcceleration().setY(m_normalGravity);
        }
        
        if ((m_bIsJetting || m_bIsBoosting) && GetParams().getVelocity().getY() > 0 ){
            GetParams().getVelocity().setY(0);
        }
    }
    
    //handle stomping
    
    if (m_bIsStomping && (!InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) &&
                          !InputHandler::Instance()->getButtonState(0, XB_DPAD_DOWN))){
        
        //Make player spin for a moment
        if (GetParams().dirLeft()){
            GetParams().setAngle(GetParams().getAngle() - (GetParams().getVelocity().getY()) - 10);
            
            
        } else if (GetParams().dirRight()){
            GetParams().setAngle(GetParams().getAngle() + (GetParams().getVelocity().getY()) + 10);
        } else {
            // m_bIsStomping = false;
        }
        
        
        m_StompCharge++;
        
        m_bIsJumping = 0;
        m_bIsJetting = 0;
        m_numJumps = 0;
        m_currentFuel = 0;
        m_bIsFalling = true;
        //GetParams().getVelocity().setX(0);
        
        
        
        
        if (m_StompCharge >= m_StompReady){
            GetParams().getAcceleration().setY(m_normalGravity*6);
            GetParams().setAngle(-180);
            GetParams().getVelocity().setX(0);
        } else {
            GetParams().getVelocity().setY(-4);
        }
        
        
    } else {
        m_StompCharge = 0;
    }
    
    //Handle Boosting
    if (m_bIsBoosting)
    {
        m_maxHorizontalSpeed = m_maxRunSpeed;
        
        if (GetParams().dirRight()){
            GetParams().setAngle(10);
            GetParams().getVelocity().setX(m_maxHorizontalSpeed);
        }
        
        if (GetParams().dirLeft()){
            GetParams().setAngle(-10);
            GetParams().getVelocity().setX(-m_maxHorizontalSpeed);
        }
        
        m_BoostTimer--;
        if (m_BoostTimer <= 0){
            m_BoostTimer = 0;
            m_horizontalSpeed = m_walkSpeed;
            m_maxHorizontalSpeed = m_maxWalkSpeed;
            m_bIsBoosting = false;
        }
    } else {
        m_maxHorizontalSpeed = m_maxWalkSpeed;
    }
    
}

void Player::handleMovement(){
    //Check Tile Collision
    //Check X movement and collision
    Vector2D<float> newPos = GetParams().getPosition();
    newPos.setX(newPos.getX() + GetParams().getVelocity().getX() + GetParams().getAcceleration().getX());
    
    //Check X collision
    if (checkCollideTile(newPos)){
        
        if (m_bCheckCollision){
            GetParams().getVelocity().setX(0);
        }
        
        //if falling downwards cling to wall
        if (GetParams().getVelocity().getY() > 0 && !m_bIsOnGround && m_bIsFalling){
            
            
            if (!m_bWallCling){
                m_numJumps++;
            }
            m_bWallCling = true;
            
            
            GetParams().getVelocity().setY(GetParams().getVelocity().getY() * .8);
        } else {
            if (m_bCheckCollision){
                GetParams().getAcceleration().setX(0);
            }
        }
        
    } else {
        m_bWallCling = false;
    }
    
    
    //Check Y Movement and Collision
    newPos = GetParams().getPosition();
    newPos.setY(newPos.getY() + GetParams().getVelocity().getY() + GetParams().getAcceleration().getY());
    
    
    //Check Y collision
    if (checkCollideTile(newPos)){
        //When hitting the ground
        if (m_bIsFalling && GetParams().getVelocity().getY() > 0) {
            m_bCanJump = true;
            m_bIsOnGround = true;
            m_numJumps = m_maxJumps;
            m_bUsedDoubleJump = false;
            m_currentFuel = m_maxFuel;
            GetParams().setAngle(0);
            
            if (GetParams().getVelocity().getY() > 1){
                SoundManager::Instance()->playSound("land_sound");
            }
        }
        
        m_bIsFalling = false;
        if (m_bCheckCollision){
            GetParams().getVelocity().setY(0);
            GetParams().getAcceleration().setY(0);
        }
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
    
    
    
    if (m_bCheckCollision){
        //Check intersection and fix
        
        //Check X intersection after move
        newPos = GetParams().getPosition();
        //Check X collision
        if (checkCollideTile(newPos)){
            GetParams().setX(GetParams().getX() - GetParams().getVelocity().getX());
            GetParams().getVelocity().setX(0);
            GetParams().getAcceleration().setX(0);
        }
        
        
        //Check Y intersection after move
        newPos = GetParams().getPosition();
        //Check Y collision
        if (checkCollideTile(newPos)){
            GetParams().setY(GetParams().getY() - GetParams().getVelocity().getY());
            GetParams().getVelocity().setY(0);
            GetParams().getAcceleration().setY(0);
        }
    }
    
    
    //Cap speed
    if (GetParams().getVelocity().getX() > m_maxHorizontalSpeed){
        GetParams().getVelocity().setX(m_maxHorizontalSpeed);
    }
    
    if (GetParams().getVelocity().getX() < -m_maxHorizontalSpeed){
        GetParams().getVelocity().setX(-m_maxHorizontalSpeed);
    }
    
    if (GetParams().getVelocity().getY() < -m_maxVerticalSpeed){
        GetParams().getVelocity().setY(-m_maxVerticalSpeed);
    }
    
    if (GetParams().getVelocity().getY() > m_maxVerticalSpeed){
        GetParams().getVelocity().setY(m_maxVerticalSpeed);
    }
    
    
    //Check if on ground
    if (m_numJumps < m_maxJumps){
        m_bOnGround = false;
    } else {
        m_bIsStomping = false;
    }
    
}


bool Player::checkCollideTile(Vector2D<float> pos){
    
    //Iterate through all collision layers
    for (vector<TileLayer*>::const_iterator it = m_pCollisionLayers.begin();
         it != m_pCollisionLayers.end() ; it++){
        
        TileLayer* pTileLayer = (*it);
        vector<vector<int>> tiles = pTileLayer->getTileIDs();
        
        //Get layers position
        //Vector2D layerPos = pTileLayer->getPosition();
        Vector2D<float> layerPos
        (pTileLayer->getPosition().getX(),
         pTileLayer->getPosition().getY());
        
        int x,y,tileColumn,tileRow,tileID = 0;
        
        //Calculate position on tile map
        x = ((layerPos.getX()) / pTileLayer->getTileSize());
        y = ((layerPos.getY()) / pTileLayer->getTileSize());
        
        //New collision detection
        Vector2D<float> startPos = pos;
        
        startPos.setX(startPos.getX() + GetParams().getWidth()/4);
        startPos.setY(startPos.getY() + GetParams().getHeight()/4);
        
        Vector2D<float> endPos
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








