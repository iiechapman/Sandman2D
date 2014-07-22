//
//  PlayState.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "CollisionManager.h"

const string PlayState::s_playID = "PLAY";

PlayState::~PlayState(){
    cout << "Deleted play state\n";
}

void PlayState::update(){
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE) ||
        InputHandler::Instance()->getButtonState(0, XB_START_BUTTON)
        ){
        Game::Instance()->getStateMachine()->pushState(new PauseState());
    }
    
    //Update all objects
    if ( !m_gameObjects.empty()){
        for (int i = 0 ; i < m_gameObjects.size(); i++){
            m_gameObjects[i]->update();
        }
    }
    
    Camera::Instance()->update();
    
    //Look for live mode
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN) && !m_EnteringLiveMode){
        setLiveMode(true);
    }
    
    if (!InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)){
        m_EnteringLiveMode = false;
    } else {
        m_EnteringLiveMode = true;
    }
    
    
    if (liveModeOn()){
        onExit();
        onEnter();
        SDL_Delay(100);
    }
    
    pLevel->update();
}

void PlayState::render(){
    //Render level
    pLevel->render();
}

bool PlayState::onEnter(){
    cout << "Entering play state\n";
    
    StateParser parser;
    parser.parseState("scripts/xm1.xml", s_playID,
                      &m_gameObjects, &m_textureIDList,&pLevelFile);
    
    LevelParser levelParser;
    
    pLevel = levelParser.parseLevel(pLevelFile.c_str());
    
    cout << "Entered play state\n";
    
    return true;
}

bool PlayState::onExit(){
    cout << "Exited play state\n";
    //setLiveMode(false);
    
    while (!m_gameObjects.empty()){
        cout << "Game Objects size: " << m_gameObjects.size() << endl;
        m_gameObjects.back()->clean();
        m_gameObjects.pop_back();
    }
    
    for (int i = 0 ; i < m_textureIDList.size() ; i++){
        TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    
    cout << "Game Objects size: " << m_gameObjects.size() << endl;
    
    m_gameObjects.clear();
    
    Camera::Instance()->reset();
    InputHandler::Instance()->reset();
    return true;
}








































































//END