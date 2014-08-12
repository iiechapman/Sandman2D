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
    bool checkCollideTile(Vector2D<double> pos);
    
    Vector2D<double> m_acceleration{0,0};

    bool m_bIsOnGround = false;
    int m_maxJumps = 2;
    int m_numJumps = m_maxJumps;
    bool m_bUsedDoubleJump = false;
    bool m_bJumpHeld;
    bool m_bCanJump;
    bool m_bOnGround;
    bool m_bIsJumping;
    bool m_bIsFalling = true;
    double m_jumpSpeed = 7;
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

    double m_jetSpeed = 0.25;
    double m_maxFuel = 100;
    double m_currentFuel = 0;
    double m_fuelCost = 1;
    bool  m_bIsJetting = false;
    
    double m_runSpeed = 8;
    double m_walkSpeed = 0.30;

    double m_horizontalSpeed = m_walkSpeed;
    double m_verticalSpeed = m_jumpSpeed;
    double m_horizontalDrag = .09;
    
    double m_maxRunSpeed = 8;
    double m_maxWalkSpeed = 4.5;
    
    double m_maxVerticalSpeed = 20;
    double m_maxHorizontalSpeed = m_maxWalkSpeed;

    double m_normalGravity = .40;
    double m_jetGravity = 0.1;
    double m_currentGravity = m_normalGravity;
    
    bool m_bCheckCollision = true;
    
    vector<TileLayer*> m_pCollisionLayers;

    
};



class PlayerCreator : public BaseCreator{
    GameObject* createGameObject() const{
        return new Player();
    }
    
};



#endif /* defined(__SDLGameDevelopmentChapter1__Player__) */
