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

//TODO Create seperate Param Objects, this is bloated!
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
    
    setAI(rhs.aiEnabled());
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

//Getters + Setters
double GameObjectParams::getX() const { return m_position.getX(); }
double GameObjectParams::getY() const { return m_position.getY(); }


double GameObjectParams::getWidth() const { return m_size.getX() * m_scale; }
double GameObjectParams::getHeight() const { return m_size.getY() * m_scale; }

double GameObjectParams::getSourceWidth() const {return m_size.getX(); }
double GameObjectParams::getSourceHeight() const {return m_size.getY(); }

int GameObjectParams::getFrame() const { return m_currentCell.getX(); }
int GameObjectParams::getRow() const { return m_currentCell.getY(); }

int GameObjectParams::getTotalFrames() const { return m_frameMax.getX();}
int GameObjectParams::getTotalRows() const { return m_frameMax.getY();}

int GameObjectParams::getCallbackID() const { return m_callbackID;}
void GameObjectParams::setCallBackID(int ID) { m_callbackID = ID; }

string GameObjectParams::getType() const { return m_type; }
void GameObjectParams::setType(string type){m_type = type;}

Vector2D<double>& GameObjectParams::getVelocity(){ return m_velocity; }
Vector2D<double>& GameObjectParams::getAcceleration(){ return m_acceleration; }
Vector2D<double>& GameObjectParams::getPosition(){ return m_position; }

string GameObjectParams::getName() const { return m_name; }
void GameObjectParams::setName(string name){m_name = name;}

string GameObjectParams::getTextureID() const { return m_textureID; }
void GameObjectParams::setTextureID(string textureID){ m_textureID = textureID; }
void GameObjectParams::setVelocity(Vector2D<double> velocity){ m_velocity = velocity;}

void GameObjectParams::setX(double x){ m_position.setX(x);}
void GameObjectParams::setY(double y){ m_position.setY(y);}

void GameObjectParams::setScale(double scale){m_scale = scale;}
double GameObjectParams::getScale(){return m_scale;}

void GameObjectParams::setWidth(double width){ m_size.setX(width); }
void GameObjectParams::setHeight(double height){ m_size.setY(height); }

double GameObjectParams::getAngle(){return m_Angle;}
void GameObjectParams::setAngle(double angle){m_Angle = angle;}

void GameObjectParams::setFrame(int frame){ m_currentCell.setX(frame); }
void GameObjectParams::setRow(int row){ m_currentCell.setY(row); }

void GameObjectParams::setMaxFrames(int frames){ m_frameMax.setX(frames); }
void GameObjectParams::setMaxRows(int rows){ m_frameMax.setY(rows); }

void GameObjectParams::setStartFrame(int frame){m_startFrame = frame;}
int GameObjectParams::getStartFrame(){return m_startFrame;}

void GameObjectParams::setAnimSpeed(int speed) { m_animSpeed = speed; }
int GameObjectParams::getAnimSpeed() { return m_animSpeed; }

bool GameObjectParams::isCollidable(){return m_bIsCollidable;}
void GameObjectParams::setCollidable(bool collidable){m_bIsCollidable = collidable;}

void GameObjectParams::setColor(SDL_Color color){m_color = color;}
SDL_Color GameObjectParams::getColor() {return m_color;}

void GameObjectParams::setBlendMode(SDL_BlendMode blendMode){m_blendMode = blendMode;}
SDL_BlendMode GameObjectParams::getBlendMode(){return m_blendMode;}

void GameObjectParams::setLockTo(string lockTo){m_lockTo = lockTo;}
string GameObjectParams::getLockTo(){return m_lockTo;}

bool GameObjectParams::isScrolling(){return m_bScrolling;}
void GameObjectParams::setScrolling(bool scrolling){m_bScrolling = scrolling;}

bool GameObjectParams::dirRight(){return m_bDirRight;}
bool GameObjectParams::dirLeft(){return m_bDirLeft;}
bool GameObjectParams::dirUp(){return m_bDirUp;}
bool GameObjectParams::dirDown(){return m_bDirDown;}

void GameObjectParams::setRight(bool right){m_bDirRight = right;}
void GameObjectParams::setLeft(bool left){m_bDirLeft = left;}
void GameObjectParams::setUp(bool up){m_bDirUp = up;}
void GameObjectParams::setDown(bool down){m_bDirDown = down;}

EventHandler* GameObjectParams::getEvents(){return &m_EventHandler;}

bool GameObjectParams::aiEnabled(){return m_bAI;}
AI_State GameObjectParams::getAIState(){return m_AIState;}
void GameObjectParams::setAIState(AI_State newState){m_AIState = newState;}
void GameObjectParams::setAI(bool AIFlag){m_bAI = AIFlag;}


















































//END