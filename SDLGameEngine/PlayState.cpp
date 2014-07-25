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
    
    //Pause game if start/escape pressed
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE) ||
        InputHandler::Instance()->getButtonState(0, XB_START_BUTTON)
        ){
        Game::Instance()->getStateMachine()->pushState(new PauseState());
    }
    
    
    //Look for live mode
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)){
        if (!m_bEnterHeld){
            setLiveMode(!liveModeOn());
        }
        m_bEnterHeld = true;
    } else {
        m_bEnterHeld = false;
    }
    

    
    //Check for modifier buttons
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)){
        //Game::Instance()->setZoom(Game::Instance()->getZoom() + 0.25);
        rumbleFactor++;
    }
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)){
        //Game::Instance()->setZoom(Game::Instance()->getZoom() - 0.25);
        rumbleFactor--;
        if (rumbleFactor <= 0){
            rumbleFactor =1;
        }
    }
    
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)){
        InputHandler::Instance()->rumbleJoystick();
        Camera::Instance()->setHorizontalRumble(rumbleFactor);
        Camera::Instance()->setVerticalRumble(rumbleFactor);
    } else {
        Camera::Instance()->resetRumble();
    }
    
    
    
    //Press enter to go into live mode
    if (!InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)){
        m_EnteringLiveMode = false;
    } else {
        m_EnteringLiveMode = true;
    }
    
    //Press button to go to next level (For Testing)
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_EQUALS)||
        InputHandler::Instance()->getButtonState(0, XB_HOME_BUTTON)){
        
        if (!m_bSwitchingLevels){
            m_bSwitchingLevels = true;
            //Setup Level from file retrieved in state
            m_currentLevel++;
            
            cout << "Max Levels = " << pLevelFiles.size() << endl;
            if (m_currentLevel > pLevelFiles.size()-1){
                m_currentLevel = 1;
            }
            
            onExit();
            LevelParser levelParser;
            string levelNumber = "level" + to_string(m_currentLevel);
            pLevel = levelParser.parseLevel(pLevelFiles[levelNumber].c_str());
        }
    } else {
        m_bSwitchingLevels = false;
    }
    
    
    //Live Mode sequence
    if (liveModeOn()){
        onExit();
        onEnter();
        SDL_Delay(100);
    }
    
    //Update all objects
    if ( !m_gameObjects.empty()){
        for (int i = 0 ; i < m_gameObjects.size(); i++){
            m_gameObjects[i]->update();
        }
    }
    
    //Update levels elements
    pLevel->update();
}

void PlayState::render(){
    //Render level
    pLevel->render();
}

bool PlayState::onEnter(){
    cout << "Entering play state\n";
    
    //Load the state from library file
    string pLevelFile;
    
    //Load levels from state file
    StateParser parser;
    parser.parseState("scripts/xm1.xml", s_playID,
                      &m_gameObjects, &m_textureIDList,&pLevelFiles);
    
    //Setup Level from file retrieved in state
    LevelParser levelParser;
    string levelNumber = "level" + to_string(m_currentLevel);
    pLevel = levelParser.parseLevel(pLevelFiles[levelNumber].c_str());
    
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