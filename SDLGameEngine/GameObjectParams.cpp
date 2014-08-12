//
//  GameObjectParams.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "GameObjectParams.h"

GameObjectParams::GameObjectParams():
GameObjectParams("null object",0,0,20,20, "null")
{
    //cout << "Null params\n";
}


GameObjectParams::GameObjectParams(string name,double x, double y,
                                   double width, double height, string textureID,
                                   int callBackID , int animSpeed):
m_name(name),
m_position(x,y),
m_size(width,height),
m_textureID(textureID),
m_frameMax(1,1),
m_currentCell(1,1),
m_acceleration(0,0),
m_callbackID(callBackID),
m_animSpeed(animSpeed),
m_blendMode(SDL_BLENDMODE_BLEND)
{
    m_color.a = 255;
    m_color.r = 255;
    m_color.g = 255;
    m_color.b = 255;
}


GameObjectParams::~GameObjectParams(){
    //cout << "Deleted game object parameters\n";
}

void GameObjectParams::operator=(GameObjectParams& rhs){
    m_position      = rhs.m_position;
    m_size          = rhs.m_size;
    m_velocity      = rhs.m_velocity;
    m_acceleration  = rhs.m_acceleration;
    m_name          = rhs.m_name;
    m_textureID     = rhs.m_textureID;
    m_animSpeed     = rhs.m_animSpeed;
    m_callbackID    = rhs.m_callbackID;
    m_blendMode     = rhs.m_blendMode;
    m_animSpeed     = rhs.m_animSpeed;
    m_startFrame    = rhs.m_startFrame;
    m_scale         = rhs.m_scale;

    setRow(rhs.getRow());
    setFrame(rhs.getFrame());
    setMaxFrames(rhs.getTotalFrames());
    
}

void GameObjectParams::printOut(){
    cout << "Parameters-" << endl;
    cout << "X: " << getX() << " " << "Y: " << getY() << endl;
    cout << "Texture ID: " << getTextureID() << endl;
    cout << "Callback ID: " << getCallbackID() << endl;
    
}








































































//END