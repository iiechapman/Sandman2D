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
    
    void handleInput();
    void handlePhysics();
    void handleAnimation();
    
private:
    Vector2D m_acceleration{0,0};
    
    bool m_bCanJump;
    bool m_bIsJumping;
    bool m_bIsFalling;
    bool m_bIsRunning;
    
    float m_runSpeed = 1.3;
    float m_walkSpeed = 0.7;
    float m_jetSpeed = .4;
    float m_jumpSpeed = 3;
    
    float m_horizontalSpeed = m_runSpeed;
    float m_verticalSpeed = m_jetSpeed;
    float m_horizontalDrag = .09;
    float m_verticalGravity = .3;
    
    
    vector<TileLayer*> m_pCollisionLayers;

    
};



class PlayerCreator : public BaseCreator{
    GameObject* createGameObject() const{
        return new Player();
    }
    
};



#endif /* defined(__SDLGameDevelopmentChapter1__Player__) */
