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
#include "EventManager.h"
#include "CollisionManager.h"
#include "TileLayer.h"


/*
 ===============================================================================
 
 Player
 Main player object
 
 ===============================================================================
 */

/*
 ====================
 Player::Player
 ====================
 */
///<Constructor used for object factory
Player::Player(){
    cout << "Created player object\n";
    m_params.setType("Player");
}


/*
 ====================
 Player::Player
 ====================
 */
///<Constructor for player, connects eventhandler and preloaded params
Player::Player(GameObjectParams params , int numberFrames)
:SDLGameObject(params){
    GetParams().setMaxFrames(numberFrames);
    EventManager::Instance()->addHandler(GetParams().getEvents());
    GetParams().getEvents()->registerEvent("set_position");
}


void Player::load(GameObjectParams params){
    SDLGameObject::load(params);
}


void Player::draw(){
    SDLGameObject::draw();
}

void Player::collision(){
    //m_params.setX(m_params.g etX() - m_params.getVelocity().getX());
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
    handleEvents();
    handleInput();
    handlePhysics();
    handleMovement();
    handleAnimation();
    
    SDLGameObject::update();
    
    //cout << "Posx: " << GetParams().getPosition().getX() << "\n";
    //cout << "Posy: " << GetParams().getPosition().getY() << "\n";
}

void Player::handleEvents(){
    while (GetParams().getEvents()->hasEvents()) {
        cout << "Handling event for player!\n";
        Event* currentEvent = GetParams().getEvents()->getTopEvent();
        
        if (currentEvent->getEventName() == string("set_position")){
            string posX = (*currentEvent->getArguments())[0];
            string posY = (*currentEvent->getArguments())[1];
            GetParams().getPosition().setX(atoi(posX.c_str()));
            GetParams().getPosition().setY(atoi(posY.c_str()));
        }
    }
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
        

        //Testing sending to event manager
        EventManager::Instance()->receiveEvent
        (new vector<Event*>
         {new Event("player", EVENT_TYPE_BROADCAST,"play_sound",
                    1, vector<string>{"jet_sound"})});
        
    
    } else {
        m_bIsJetting = false;
    }
    
    if ((InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) ||
         InputHandler::Instance()->getButtonState(0, XB_DPAD_DOWN)) &&
        m_bIsStomping == false){
        
        //Testing sending to event manager
        EventManager::Instance()->receiveEvent
        (new vector<Event*>
         {new Event("player", EVENT_TYPE_BROADCAST,"play_sound",
                    1, vector<string>{"stomp_sound"})});
        m_bIsStomping = true;
    }
    
    
    //Jump Button
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_X) ||
        InputHandler::Instance()->getButtonState(0, XB_A_BUTTON)){
        if (!m_bJumpHeld && m_numJumps > 0 && !m_bUsedDoubleJump){
            m_bIsJumping = true;
            m_numJumps--;
            
            //Testing sending to event manager
            EventManager::Instance()->receiveEvent
            (new vector<Event*>
            {new Event("player", EVENT_TYPE_BROADCAST,"play_sound",
                       1, vector<string>{"jump_sound"})});
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
        //Testing sending to event manager
        EventManager::Instance()->receiveEvent
        (new vector<Event*>
         {new Event("player", EVENT_TYPE_BROADCAST,"play_sound",
                    1, vector<string>{"boost_sound"})});
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
    if (m_bIsJetting && !(GetParams().getVelocity().getY() == 0 ) && m_currentFuel > m_fuelCost){
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
    Vector2D<double> newPos = GetParams().getPosition();
    newPos.setX(newPos.getX() + GetParams().getVelocity().getX() + GetParams().getAcceleration().getX());
    
    //Check X collision
    if (checkCollideWithTile(newPos)){
        
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
    if (checkCollideWithTile(newPos)){
        //When hitting the ground
        if (m_bIsFalling && GetParams().getVelocity().getY() > 0) {
            m_bCanJump = true;
            m_bIsOnGround = true;
            m_numJumps = m_maxJumps;
            m_bUsedDoubleJump = false;
            m_currentFuel = m_maxFuel;
            GetParams().setAngle(0);
            
            if (GetParams().getVelocity().getY() > 1){
                //Testing sending to event manager
                EventManager::Instance()->receiveEvent
                (new vector<Event*>
                 {new Event("player", EVENT_TYPE_BROADCAST,"play_sound",
                            1, vector<string>{"land_sound"})});
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
        if (checkCollideWithTile(newPos)){
            GetParams().setX(GetParams().getX() - GetParams().getVelocity().getX());
            GetParams().getVelocity().setX(0);
            GetParams().getAcceleration().setX(0);
        }
        
        
        //Check Y intersection after move
        newPos = GetParams().getPosition();
        //Check Y collision
        if (checkCollideWithTile(newPos)){
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

void Player::clean(){
    SDLGameObject::clean();
    cout << "Cleaning player\n";
}

























































//END