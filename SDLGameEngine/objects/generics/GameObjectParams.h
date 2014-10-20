//
//  GameObjectParams.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__GameObjectParams__
#define __LudumDare29__GameObjectParams__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "Vector2D.h"
#include "EventHandler.h"

using namespace std;


enum AI_State{
    MOVE_NONE,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_STOP
};

//TODO: Create seperate Param objects, ie AI params, RenderParams,MovementParams

class GameObjectParams{
public:
    GameObjectParams();
    GameObjectParams(string name,double x, double y,
                     double width, double height,
                     string textureID,int callbackID = 0 , int animSpeed = 1);
    
    ~GameObjectParams();
    
    //Helper Methods
    void printOut();
    void operator=(GameObjectParams& rhs);
    
    //Identity Methods
    int getCallbackID() const;
    void setCallBackID(int ID);
    
    string getType() const;
    void setType(string type);
    
    string getName() const;
    void setName(string name);
    
    //Movement Methods
    Vector2D<double>& getVelocity();
    Vector2D<double>& getAcceleration();
    Vector2D<double>& getPosition();
    
    void setLockTo(string lockTo);
    string getLockTo();
    
    //Camera Methods
    bool isScrolling();
    void setScrolling(bool scrolling);
    
    //Direction Methods
    bool dirRight();
    bool dirLeft();
    bool dirUp();
    bool dirDown();
    void setRight(bool right);
    void setLeft(bool left);
    void setUp(bool up);
    void setDown(bool down);
    
    
    //Render Methods
    string getTextureID() const;
    void setTextureID(string textureID);
    void setVelocity(Vector2D<double> velocity);
    
    double getX() const;
    double getY() const;
    
    double getWidth() const;
    double getHeight() const;
    
    double getSourceWidth() const;
    double getSourceHeight() const;
    
    int getFrame() const;
    int getRow() const;
    
    int getTotalFrames() const;
    int getTotalRows() const;
    
    void setX(double x);
    void setY(double y);
    
    void setScale(double scale);
    double getScale();
    
    void setWidth(double width);
    void setHeight(double height);
    
    double getAngle();
    void setAngle(double angle);
    
    void setColor(SDL_Color color);
    SDL_Color getColor();
    
    void setBlendMode(SDL_BlendMode blendMode);
    SDL_BlendMode getBlendMode();
    
    //Animation Params
    void setFrame(int frame);
    void setRow(int row);
    
    void setMaxFrames(int frames);
    void setMaxRows(int rows);

    void setStartFrame(int frame);
    int getStartFrame();
    
    void setAnimSpeed(int speed);
    int getAnimSpeed();
    
    
    //Event Methods
    EventHandler* getEvents();
    bool isCollidable();
    void setCollidable(bool collidable);
    
    //AI Methods
    bool aiEnabled();
    AI_State getAIState();
    void setAIState(AI_State newState);
    void setAI(bool AIFlag);

    friend class GameObject;
    
protected:
    //Size vars
    Vector2D<double> m_position;
    Vector2D<double> m_size;
    
    //Physics vars
    Vector2D<double> m_velocity;
    Vector2D<double> m_acceleration;
    bool m_bIsCollidable;
    
    //Animation vars
    int m_startFrame;
    Vector2D<double> m_currentCell;
    Vector2D<double> m_frameMax;
    int m_callbackID;
    int m_animSpeed;

    //Texture vars
    string m_name = "";
    string m_type = "";
    string m_textureID = "";
    string m_lockTo = "";
    double m_Angle = 0.0;
    SDL_Color m_color = SDL_Color{200,100,90};
    SDL_BlendMode m_blendMode = SDL_BLENDMODE_BLEND;
    double m_scale = 1.0;
    
    //Updating vars
    bool m_bScrolling = true;
    bool m_bUpdating = false;
    bool m_bDead = false;
    bool m_bDying = false;
    
    //Direction vars;
    bool m_bDirRight = true;
    bool m_bDirLeft = false;
    bool m_bDirUp = false;
    bool m_bDirDown = false;

    //Event Handling
    EventHandler m_EventHandler;
    
    
    //AI testing
    bool m_bAI = false;
    AI_State m_AIState = MOVE_NONE;
    
};

#endif /* defined(__LudumDare29__GameObjectParams__) */
































//END