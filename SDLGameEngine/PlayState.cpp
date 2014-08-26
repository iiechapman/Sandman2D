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
#include "SoundManager.h"
#include "EventManager.h"
#include "EventHandler.h"

const string PlayState::s_playID = "PLAY";

PlayState::PlayState(){
    m_handler.registerEvent("next_level");
    EventManager::Instance()->addHandler(&m_handler);
}

PlayState::~PlayState(){
    cout << "Deleted play state\n";
}

void PlayState::update(){
    //handle Events
    while (m_handler.hasEvents()) {
        cout << "Handling event for player!\n";
        Event* currentEvent = m_handler.getTopEvent();
        
        if (currentEvent->getEventName() == string("next_level")){
            loadNextLevel();
        }
        
    }
    
    //Pause game if start/escape pressed
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE) ||
        InputHandler::Instance()->getButtonState(0, XB_START_BUTTON)
        ){
        Game::Instance()->getStateMachine()->pushState(new PauseState());
    }
    
    
    //Look for live mode
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)){
        if (!m_bEnterHeld){
            Game::Instance()->setLiveMode(!Game::Instance()->isLiveModeOn());
        }
        m_bEnterHeld = true;
    } else {
        m_bEnterHeld = false;
    }
    
    
    
    //Check for modifier buttons
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)){
        //Game::Instance()->setZoom(Game::Instance()->getGlobalZoom() + 0.25);
        rumbleFactor++;
    }
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)){
        //Game::Instance()->setZoom(Game::Instance()->getGlobalZoom() - 0.25);
        rumbleFactor--;
        if (rumbleFactor <= 0){
            rumbleFactor =1;
        }
    }
    
    
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)){
        InputHandler::Instance()->rumbleJoystick();
        
        //Testing sending to event manager
        EventManager::Instance()->receiveEvent
        (new vector<Event*>
         {new Event("player", EVENT_TYPE_BROADCAST,"play_sound",
                    1, vector<string>{"explosion_sound"})});
        
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
        loadNextLevel();
    }
    
    
    //Live Mode sequence
    if (Game::Instance()->isLiveModeOn()){
        cout << "Live mode enabled\n";
        onExit();
        onEnter();
        SDL_Delay(100);
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
    parser.loadState("res/lib/xml/library.xml", this);
    
    //Setup Level from file retrieved in state
    LevelParser levelParser;
    string levelNumber = "level" + to_string(m_currentLevel);
    pLevel = levelParser.parseLevel(pLevelFiles[levelNumber].c_str(), this);
    
    //Testing sending to event manager
    EventManager::Instance()->receiveEvent
    (new vector<Event*>
     {new Event("play_state", EVENT_TYPE_BROADCAST,"play_song",
                1, vector<string>{"level_song"})});
    
    
    //Testing sending to event manager
    EventManager::Instance()->receiveEvent
    (new vector<Event*>
     {new Event("play_state", EVENT_TYPE_BROADCAST,"song_volume",
                1, vector<string>{"40"})});
    
    
    cout << "Entered play state\n";
    
    return true;
}

bool PlayState::onExit(){
    cout << "Exiting play state\n";
    
    //    while (!m_gameObjects.empty()){
    //        cout << "Game Objects size: " << m_gameObjects.size() << endl;
    //        if (m_gameObjects.back()->GetParams().getName() != "Player"){
    //            cout << "Deleting " <<m_gameObjects.back()->GetParams().getName() << endl;
    //            m_gameObjects.back()->clean();
    //            m_gameObjects.pop_back();
    //
    //        } else {
    //            cout << "Not Deleting the player!\n";
    //        }
    //    }
    
    pLevel->clean();
    
    for (int i = 0 ; i < m_textureIDList.size() ; i++){
        //TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    
    cout << "Game Objects size: " << m_gameObjects.size() << endl;
    
    //m_gameObjects.clear();
    
    if (!Game::Instance()->isLiveModeOn()){
        Camera::Instance()->reset();
        InputHandler::Instance()->reset();
    }
    
    SoundManager::Instance()->stopSong();
    return true;
}

void PlayState::loadNextLevel(){
    if (!m_bSwitchingLevels){
        m_bSwitchingLevels = true;
        
        m_currentLevel++;
        
        cout << "Max Levels = " << pLevelFiles.size() << endl;
        if (m_currentLevel > pLevelFiles.size()-1){
            m_currentLevel = 0;
        }
        
        onExit();
        onEnter();
    } else {
        m_bSwitchingLevels = false;
    }
}




































































//END