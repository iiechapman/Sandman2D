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
    
//    //Check for move past X bounds right
//    if (m_pTarget->getX() > Game::Instance()->getGameWidth()/2){
//        m_position.setX(m_position.getX() +
//                        (m_pTarget->getX() - Game::Instance()->getGameWidth()/2));
//        
//        m_pTarget->setX(m_pTarget->getX() -
//                        (m_pTarget->getX() - Game::Instance()->getGameWidth()/2));
//    }
//    
//    //Check for move past X bounds left
//    if (m_pTarget->getX() < Game::Instance()->getGameWidth()/2){
//        m_position.setX(m_position.getX() -
//                        (Game::Instance()->getGameWidth()/2) + m_pTarget->getX());
//        
//        m_pTarget->setX(m_pTarget->getX() +
//                        (Game::Instance()->getGameWidth()/2) - m_pTarget->getX());
//    }
//    
//    
//    //Check for move past Y bounds bottom
//    if (m_pTarget->getY() > Game::Instance()->getGameHeight()/2){
//        cout << "m_PTarY: " << m_pTarget->getY() << endl;
//        m_position.setY(m_position.getY() +
//                        (m_pTarget->getY() - Game::Instance()->getGameHeight()/2));
//        
//        m_pTarget->setY(m_pTarget->getY() -
//                        (m_pTarget->getY() - Game::Instance()->getGameHeight()/2));
//    }
//    
//    //Check for move past Y bounds top
//    if (m_pTarget->getY() < Game::Instance()->getGameHeight()/2){
//        m_position.setY(m_position.getY() -
//                        (Game::Instance()->getGameHeight()/2) + m_pTarget->getY());
//        
//        m_pTarget->setY(m_pTarget->getY() +
//                        (Game::Instance()->getGameHeight()/2) - m_pTarget->getY());
//    }
//    
//    
    
}

void Camera::reset(){
    m_position.setX(0);
    m_position.setY(0);
}

//Camera position is updated and sent back to caller
const Vector2D Camera::getPosition(){
    
    //If camera target is set, follow it
    if (m_pTarget !=0){
        Vector2D pos(((m_pTarget->getX()) - ((Game::Instance()->getGameWidth() / Game::Instance()->getZoom())/2)),
                     (m_pTarget->getY()) - ((Game::Instance()->getGameHeight() / Game::Instance()->getZoom())/2));
        
        
    
        //Bounds for camera
        if (pos.getX() < 0){
            pos.setX(0);
        }
        
        if (pos.getY() < 0){
            pos.setY(0);
        }
        
        
        // cout << "Pos x: " << ((Game::Instance()->getGameWidth()/2)) << endl;
        
        
        //Check if camera has scrolled past tiles, rework this equation
        if (pos.getX() > Game::Instance()->getMapWidth() - (Game::Instance()->getGameWidth()/ Game::Instance()->getZoom())){
            
            pos.setX( Game::Instance()->getMapWidth() - (Game::Instance()->getGameWidth())/ Game::Instance()->getZoom());
        }
        
        
        if (pos.getY() > Game::Instance()->getMapHeight() - (Game::Instance()->getGameHeight()/ Game::Instance()->getZoom())){
            pos.setY(Game::Instance()->getMapHeight() - (Game::Instance()->getGameHeight()/ Game::Instance()->getZoom() ));
        }
    
        pos.setX(pos.getX() + m_rumbleHorizontal);
        pos.setY(pos.getY() + m_rumbleVertical);
        
        
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