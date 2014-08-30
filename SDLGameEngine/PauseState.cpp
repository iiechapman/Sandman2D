//
//  PauseState.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "PauseState.h"
#include "Game.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "MainMenuState.h"

const string PauseState::s_pauseID = "PAUSE";

PauseState::~PauseState(){
    cout << "Deleted menu\n";
}

void PauseState::setCallbacks(const vector<Callback>& callbacks){
    cout << "Setting callback functions\n";
    
    //Check all game objects
    for (int i = 0 ; i < m_gameObjects.size(); i++){

        //check if Menu Buttons through cast
        if (dynamic_cast<MenuButton*>(m_gameObjects[i])){
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void PauseState::update(){
    if ( !m_gameObjects.empty()){
        for (int i = 0 ; i < m_gameObjects.size(); i++){
            m_gameObjects[i]->update();
        }
    }
}

void PauseState::render(){
    for (int i = 0 ; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }
}

bool PauseState::onEnter(){
    cout << "Entered menu\n";
    
    StateParser parser;
    parser.parseState("res/lib/xml/library.xml", s_pauseID, &m_gameObjects, &m_textureIDList,NULL);
    
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_ResumeButton);  // Resume Button = 1
    m_callbacks.push_back(s_MenuButton);    // Menu Button = 2
 
    setCallbacks(m_callbacks);
    
    cout << "Game Objects on enter " << m_gameObjects.size() << endl;
    
    return true;
}

bool PauseState::onExit(){
    while (!m_gameObjects.empty()){
        cout << "Game Objects size: " << m_gameObjects.size() << endl;
        m_gameObjects.back()->clean();
        m_gameObjects.pop_back();
    }
    
    cout << "Game Objects size: " << m_gameObjects.size() << endl;
    
    m_gameObjects.clear();
    
    //Clearing Textures
    for (int i = 0 ; i < m_textureIDList.size() ; i++ ){
        //TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    
    
    InputHandler::Instance()->reset();
    
    cout << "Exited menu\n";
    return true;
}

void PauseState::s_ResumeButton(){
    cout << "Pressed resume button\n";
    Game::Instance()->getStateMachine()->popState();
}

void PauseState::s_MenuButton() {
    cout << "Pressed menu button\n";
    Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}

















































//END