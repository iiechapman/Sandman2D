//
//  Camera.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 7/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Camera.h"
#include "Game.h"


Camera* Camera::s_pCamera = 0;

//Camera position is updated and sent back to caller
const Vector2D Camera::getPosition(){
    //If camera target is set, follow it
    if (m_pTarget !=0){
        Vector2D pos(m_pTarget->getX() - (Game::Instance()->getGameWidth()/2),
                     m_pTarget->getY() - (Game::Instance()->getGameHeight()/2));
        
        if (pos.getX() < 0){
            pos.setX(0);
        }
        
        if (pos.getY() < 0){
            pos.setY(0);
        }
        
        if (pos.getX() > Game::Instance()->getGameWidth()){
            pos.setX(Game::Instance()->getGameWidth());
        }
        
        if (pos.getY() > Game::Instance()->getMapHeight()){
            pos.setY(Game::Instance()->getMapHeight());
        }
        
        
        //If target is farther than camera move towards it
        if (m_position.getX() < pos.getX()) {
            m_position.setX(m_position.getX() + .001);
        }
        
        if (m_position.getX() > pos.getX()) {
            m_position.setX(m_position.getX() - .001);
        }
        
        if (!m_bSmoothScroll){
        return pos;
        }
    }
    //If no target set or smooth scroll, return position as is
    return m_position;
}

Camera::Camera(){
    //Created camera
}

Camera::~Camera(){
    //Deleted camera
}