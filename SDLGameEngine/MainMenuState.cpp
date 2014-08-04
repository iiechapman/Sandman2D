//
//  MainMenuState.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/17/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "MainMenuState.h"
#include "StateParser.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"

const string MainMenuState::s_mainMenuID = "MAINMENU";

MainMenuState::MainMenuState(){
    cout << "Main Menu created\n";
}

MainMenuState::~MainMenuState(){
 cout << "Deleted Main Menu\n";
}

bool MainMenuState::onEnter(){
    
    //Parse the state from the XML file
    StateParser parser;
    
    parser.parseState
    ("res/lib/xml/Library.xml", s_mainMenuID, &m_gameObjects, &m_textureIDList,NULL);

    //Load callback functions to list of callbacks
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_PlayButton);
    m_callbacks.push_back(s_ExitButton);
    
    setCallbacks(m_callbacks);
    
    cout << "Game Objects on enter " << m_gameObjects.size() << endl;
    
    cout << "Entering Main Menu State\n";
    
    return true;
}

void MainMenuState::update(){
    if ( !m_gameObjects.empty()){
        for (int i = 0 ; i < m_gameObjects.size(); i++){
            m_gameObjects[i]->update();
        }
    }
}

void MainMenuState::render(){
    for (int i = 0 ; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }
}

void MainMenuState::setCallbacks(const vector<Callback> &callbacks){
    //Run through all game Objects
    for (int i = 0 ; i < m_gameObjects.size() ; i++ ){
        
        //Check if game object is a button, set callback appropriately
        if (dynamic_cast<MenuButton*>(m_gameObjects[i])){
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            cout << "Callback set to " << pButton->getCallbackID() << endl;
            pButton->setCallback(m_callbacks[pButton->getCallbackID()]);
        }
    }
    
    
}

bool MainMenuState::onExit(){
    //Run through all textures, and clear them out of texture manager
    for (int i = 0 ; i < m_textureIDList.size() ; i++){
        //TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    
    while (!m_gameObjects.empty()){
        cout << "Game Objects size: " << m_gameObjects.size() << endl;
        m_gameObjects.back()->clean();  
        m_gameObjects.pop_back();
    }
    
    cout << "Game Objects size: " << m_gameObjects.size() << endl;
    
    m_gameObjects.clear();

    Camera::Instance()->reset();
    
    return true;
}

void MainMenuState::s_PlayButton(){
    cout << "Pressed play button\n";
    
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_ExitButton() {
    cout << "Pressed exit button\n";
    Game::Instance()->quit();
}








































































//END