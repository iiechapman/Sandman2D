//
//  MenuButton.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "MenuButton.h"
#include "Game.h"

MenuButton::MenuButton(){
}

void MenuButton::load(GameObjectParams params){
    SDLGameObject::load(params);
    GetParams().setFrame(MOUSE_OUT);
    
}

void MenuButton::draw(){
    SDLGameObject::draw();
}

void MenuButton::update(){
    Vector2D* pMousePos = InputHandler::Instance()->getMousePosition();
    
    float zoom = Game::Instance()->getZoom();
    
    if (pMousePos->getX() < GetParams().getX() +
        GetParams().getWidth() * zoom &&
        pMousePos->getX() > GetParams().getX() * zoom  &&
        pMousePos->getY() < GetParams().getY() * zoom +
        GetParams().getHeight()* zoom  &&
        pMousePos->getY() > GetParams().getY() * zoom
        ){
        GetParams().setFrame(MOUSE_OVER);
        
        if (InputHandler::Instance()->getMouseButtonState(LEFT)){
            GetParams().setFrame(MOUSE_CLICKED);
            if (m_bReleased && m_callback){
                m_callback();
                m_bReleased = false;
            }
        } else{
            m_bReleased = true;
        }
    } else {
        GetParams().setFrame(MOUSE_OUT);
    }
    
}

void MenuButton::clean(){
    cout << "Cleaning up button\n";
    SDLGameObject::clean();
}

void MenuButton::collision(){
    
}







































































//END