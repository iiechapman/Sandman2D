//
//  GameOverState.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "PlayState.h"
#include "GameOverState.h"
#include "Game.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "StateParser.h"


const string GameOverState::s_gameOverID = "GAMEOVER";

GameOverState::~GameOverState(){
    cout << "Deleted game over state\n";
}

void GameOverState::update(){
    if ( !m_gameObjects.empty()){
        for (int i = 0 ; i < m_gameObjects.size(); i++){
            m_gameObjects[i]->update();
        }
    }
}

void GameOverState::render(){
    for (int i = 0 ; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }
}

void GameOverState::setCallbacks(const vector<Callback>& callbacks){
    for (int i = 0 ; i < m_gameObjects.size(); i++){
        if (dynamic_cast<MenuButton*>(m_gameObjects[i])){
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

bool GameOverState::onEnter(){
    cout << "Entered game over state\n";

    //Load parser with XML file and create objects/textures for scene
    StateParser parser;
    parser.parseState
    ("res/lib/xml/library.xml", s_gameOverID, &m_gameObjects, &m_textureIDList,NULL);
    
    cout << "Game Objects on enter " << m_gameObjects.size() << "\n";
    
    cout << "Setting callbacks\n";
    
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_RestartButton);
    
    setCallbacks(m_callbacks);
    
    return true;
}

bool GameOverState::onExit(){
    while (!m_gameObjects.empty()){
        cout << "Game Objects size: " << m_gameObjects.size() << "\n";
        m_gameObjects.back()->clean();
        m_gameObjects.pop_back();
    }
    
    cout << "Game Objects size: " << m_gameObjects.size() << "\n";
    
    m_gameObjects.clear();
    
    for (int i = 0 ; i < m_textureIDList.size() ; i++ ){
        //TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    
    
    InputHandler::Instance()->reset();
    
    cout << "Exited menu\n";
    return true;
}

void GameOverState::s_RestartButton(){
    cout << "Pressed play button\n";
    
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}
















































//END