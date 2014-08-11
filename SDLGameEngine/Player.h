//
//  Player.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__Player__
#define __SDLGameDevelopmentChapter1__Player__

#include <iostream>
#include <vector>
#include "SDLGameObject.h"
#include "GameObjectFactory.h"


class TileLayer;

//inherit from sdlgameobject
class Player : public SDLGameObject {
public:
    Player();
    Player(GameObjectParams params, int numberFrames);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(GameObjectParams params);
    virtual void collision();
    
    void setCollisionLayers(vector<TileLayer*> collisionLayers){
        m_pCollisionLayers = collisionLayers;
    }
    
private:
    void handleInput();
    void handlePhysics();
    void handleMovement();
    void handleAnimation();
    bool checkCollideTile(Vector2D<float> pos);
    
    Vector2D<float> m_acceleration{0,0};

    bool m_bIsOnGround = false;
    int m_maxJumps = 2;
    int m_numJumps = m_maxJumps;
    bool m_bUsedDoubleJump = false;
    bool m_bJumpHeld;
    bool m_bCanJump;
    bool m_bOnGround;
    bool m_bIsJumping;
    bool m_bIsFalling = true;
    float m_jumpSpeed = 7;
    bool m_bWallCling = false;
    
    bool m_bIsStomping = false;
    int m_StompCharge = 0;
    int m_StompReady = 20;
    bool m_bIsReadyToStomp = false;
    
    bool m_bIsBoosting = false;
    bool m_bBoostHeld = false;
    int m_BoostTime = 15;
    int m_BoostTimer = 0;

    bool m_bMoveRight;
    bool m_bMoveLeft;    

    float m_jetSpeed = 0.15;
    float m_maxFuel = 100;
    float m_currentFuel = 0;
    float m_fuelCost = 1;
    bool  m_bIsJetting = false;
    
    float m_runSpeed = 8;
    float m_walkSpeed = 0.30;

    float m_horizontalSpeed = m_walkSpeed;
    float m_verticalSpeed = m_jumpSpeed;
    float m_horizontalDrag = .09;
    
    float m_maxRunSpeed = 8;
    float m_maxWalkSpeed = 4.5;
    
    float m_maxVerticalSpeed = 20;
    float m_maxHorizontalSpeed = m_maxWalkSpeed;

    float m_normalGravity = .40;
    float m_jetGravity = 0.1;
    float m_currentGravity = m_normalGravity;
    
    bool m_bCheckCollision = true;
    
    vector<TileLayer*> m_pCollisionLayers;

    
};



class PlayerCreator : public BaseCreator{
    GameObject* createGameObject() const{
        return new Player();
    }
    
};



#endif /* defined(__SDLGameDevelopmentChapter1__Player__) */
