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

void Camera::update(){
    
    //Set rumble factor
    if (m_rumbleVertical != 0 && m_rumbleHorizontal !=0){
        m_currentHorRumble = -rand() % m_rumbleHorizontal + rand() % m_rumbleHorizontal;
        m_currentVertRumble =-rand() % m_rumbleVertical + rand() % m_rumbleVertical;
    }

}

void Camera::reset(){
    m_position.setX(0);
    m_position.setY(0);
}

//Camera position is updated and sent back to caller
const Vector2D<double> Camera::getPosition(){
    
    //If camera target is set, follow it
    if (m_pTarget !=0){
        Vector2D<double> pos(((m_pTarget->getX()) - ((Game::Instance()->getGameWidth() / Game::Instance()->getZoom())/2)),
                     (m_pTarget->getY()) - ((Game::Instance()->getGameHeight() / Game::Instance()->getZoom())/2));
        
        
    
        //Bounds for camera
        if (pos.getX() < 0){
            pos.setX(0);
        }
        
        if (pos.getY() < 0){
            pos.setY(0);
        }
        
        
        //Check if camera has scrolled past tiles, rework this equation
        if (pos.getX() > Game::Instance()->getMapWidth() - (Game::Instance()->getGameWidth()/ Game::Instance()->getZoom())){
            pos.setX( Game::Instance()->getMapWidth() - (Game::Instance()->getGameWidth())/ Game::Instance()->getZoom());
        }
        
        
        if (pos.getY() > Game::Instance()->getMapHeight() - (Game::Instance()->getGameHeight()/ Game::Instance()->getZoom())){
            pos.setY(Game::Instance()->getMapHeight() - (Game::Instance()->getGameHeight()/ Game::Instance()->getZoom() ));
        }
    
        
        //Add rumble
        pos.setX(pos.getX() + m_currentHorRumble);
        pos.setY(pos.getY() + m_currentVertRumble);
        
        
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