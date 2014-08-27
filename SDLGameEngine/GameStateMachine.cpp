//
//  GameStateMachine.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "GameStateMachine.h"

void GameStateMachine::update(){
    if (!m_gameStates.empty()){
        //cout << "!!Current State: " << m_gameStates.back()->getStateID() << endl;
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render(){
    if (!m_gameStates.empty()){
        m_gameStates.back()->render();
    }
}

void GameStateMachine::pushState(IGameState* pState){
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::popState(){
    if (!m_gameStates.empty()){
        if (m_gameStates.back()->onExit()){
            m_gameStates.pop_back();
        }
    }
}

void GameStateMachine::changeState(IGameState* pState){
    if (!m_gameStates.empty()){
        if (m_gameStates.back()->getStateID() == pState->getStateID()){
            //Same state, do nothing
            //cout << "Same state!\n";
            return;
        }
        cout << "DELETING " << m_gameStates.back()->getStateID() << endl;
        popState();
    }
    
    pState->onEnter();
    
    m_gameStates.push_back(pState);
    cout << "STARTING " << m_gameStates.back()->getStateID() << endl;
    
}







































































//END