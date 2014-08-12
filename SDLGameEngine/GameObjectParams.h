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

using namespace std;

class GameObjectParams{
public:
    GameObjectParams();
    GameObjectParams(string name,double x, double y,
                     double width, double height,
                     string textureID,int callbackID = 0 , int animSpeed = 1);
    
    ~GameObjectParams();
    
    void operator=(GameObjectParams& rhs);
    
    void printOut();
    
    double getX() const { return m_position.getX(); }
    double getY() const { return m_position.getY(); }
    
    double getWidth() const { return m_size.getX() * m_scale; }
    double getHeight() const { return m_size.getY() * m_scale; }
    
    double getSourceWidth() const {return m_size.getX(); }
    double getSourceHeight() const {return m_size.getY(); }
    
    int getFrame() const { return m_currentCell.getX(); }
    int getRow() const { return m_currentCell.getY(); }
    
    int getTotalFrames() const { return m_frameMax.getX();}
    int getTotalRows() const { return m_frameMax.getY();}
    
    int getCallbackID() const { return m_callbackID;}
    
    void setCallBackID(int ID) { m_callbackID = ID; } 
    
    string getType() const { return m_type; }
    
    void setType(string type){
        m_type = type;
    }

    Vector2D<double>& getVelocity(){ return m_velocity; }
    Vector2D<double>& getAcceleration(){ return m_acceleration; }
    Vector2D<double>& getPosition(){ return m_position; }
    
    string getName() const { return m_name; }
    void setName(string name){
        m_name = name;
    }
    string getTextureID() const { return m_textureID; }
    
    void setTextureID(string textureID){ m_textureID = textureID; }
    void setVelocity(Vector2D<double> velocity){ m_velocity = velocity;}
    
    void setX(double x){ m_position.setX(x);}
    void setY(double y){ m_position.setY(y);}
    
    void setScale(double scale){
        m_scale = scale;
    }
    double getScale(){
        return m_scale;
    }
    
    void setWidth(double width){ m_size.setX(width); }
    void setHeight(double height){ m_size.setY(height); }
    
    double getAngle(){
        return m_Angle;
    }
    void setAngle(double angle){
        m_Angle = angle;
    }
    
    void setFrame(int frame){ m_currentCell.setX(frame); }
    void setRow(int row){ m_currentCell.setY(row); }
    
    void setMaxFrames(int frames){ m_frameMax.setX(frames); }
    void setMaxRows(int rows){ m_frameMax.setY(rows); }

    void setStartFrame(int frame){
        m_startFrame = frame;
    }
    int getStartFrame(){
        return m_startFrame;
    }
    
    void setAnimSpeed(int speed) { m_animSpeed = speed; }
    int getAnimSpeed() { return m_animSpeed; }
    
    bool isCollidable(){
        return m_bIsCollidable;
    }
    void setCollidable(bool collidable){
        m_bIsCollidable = collidable;
    }
    
    void setColor(SDL_Color color){
        m_color = color;
    }
    
    SDL_Color getColor() {
        return m_color;
    }
    void setBlendMode(SDL_BlendMode blendMode){
        m_blendMode = blendMode;
    }
    SDL_BlendMode getBlendMode(){
        return m_blendMode;
    }
    
    void setLockTo(string lockTo){
        m_lockTo = lockTo;
    }
    string getLockTo(){
        return m_lockTo;
    }
    
    bool isScrolling(){
        return m_bScrolling;
    }
    void setScrolling(bool scrolling){
        m_bScrolling = scrolling;
    }
    
    bool dirRight(){
        return m_bDirRight;
    }
    bool dirLeft(){
        return m_bDirLeft;
    }
    bool dirUp(){
        return m_bDirUp;
    }
    bool dirDown(){
        return m_bDirDown;
    }
    
    void setRight(bool right){
        m_bDirRight = right;
    }
    void setLeft(bool left){
        m_bDirLeft = left;
    }
    void setUp(bool up){
        m_bDirUp = up;
    }
    void setDown(bool down){
        m_bDirDown = down;
    }
    
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
    string m_name;
    string m_type;
    string m_textureID;
    string m_lockTo;
    double m_Angle;
    SDL_Color m_color;
    SDL_BlendMode m_blendMode;
    double m_scale = 1.0;
    
    //Updating vars
    bool m_bScrolling = true;
    bool m_bUpdating;
    bool m_bDead;
    bool m_bDying;
    
    //Direction vars;
    bool m_bDirRight = true;
    bool m_bDirLeft = false;
    bool m_bDirUp = false;
    bool m_bDirDown = false;

};

#endif /* defined(__LudumDare29__GameObjectParams__) */








































































//END