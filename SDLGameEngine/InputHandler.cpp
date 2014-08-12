//
//  InputHandler.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <SDL2/SDL.h>
#include "Game.h"
#include "InputHandler.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler* InputHandler::Instance(){
    if (!s_pInstance){
        s_pInstance = new InputHandler();
    }
    return s_pInstance;
}

InputHandler::InputHandler()
{
    //Init mouse buttons
    for (int i = 0 ; i < 3; i++){
        m_mouseButtonStates.push_back(false);
    }
    
    m_mousePosition = new Vector2D(0,0);
    
    updateKeys();
    
    cout << "Created input handler\n";
}

InputHandler::~InputHandler(){
    cout << "Deleted InputHandler\n";
}

void InputHandler::update(){
    
    if (SDL_NumJoysticks() < 1){
        if (m_bJoystickInitialized){
            cout << "Joystick Disconnected!\n";
        }
        
        m_bJoystickInitialized = false;
        
    } else if (!m_bJoystickInitialized){
        initializeJoysticks();
        cout << "Joystick Connected!\n";
    }
    
    SDL_Event p_event;
    
    while (SDL_PollEvent(&p_event)) {
        switch (p_event.type)
        {
            case SDL_QUIT:{
                Game::Instance()->quit();
                break;
            }
                
                //Mouse Handling
            case SDL_MOUSEBUTTONDOWN:{
                onMouseButtonDown(p_event);
                break;
            }
                
                
            case SDL_MOUSEBUTTONUP:{
                onMouseButtonUp(p_event);
                break;
            }
                
            case SDL_MOUSEMOTION:{
                updateMousePosition(p_event);
                break;
            }
                
                //Keyboard Handling
            case SDL_KEYDOWN:{
                {
                    if (p_event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        //Game::Instance()->quit();
                    }
                    
                    updateKeys();
                    break;
                }
            }
                
            case SDL_KEYUP:{
                updateKeys();
                break;
            }
                
            case SDL_JOYBUTTONDOWN:{
                onJoystickButtonDown(p_event);
                break;
            }
                
            case SDL_JOYBUTTONUP:{
                onJoystickButtonUp(p_event);
                break;
            }
                
            case SDL_JOYAXISMOTION:{
                onJoystickMotion(p_event);
                
                break;
            }
        }
	}
}

void InputHandler::clean(){
    if (m_keystates){
        m_keystates = 0;
    }
    m_keystates = 0;
    
    if (s_pInstance){
        delete s_pInstance;
    }
    m_joysticks.clear();
}

void InputHandler::reset(){
    m_mouseButtonStates[LEFT] = false;
    m_mouseButtonStates[RIGHT] = false;
    m_mouseButtonStates[MIDDLE] = false;
}

//Keyboard Handling
void InputHandler::updateKeys(){
    m_keystates = SDL_GetKeyboardState(0);
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
    if (m_keystates != NULL){
        return m_keystates[key];
    }
    
    return false;
}

//Mouse Handling
Vector2D* InputHandler::getMousePosition(){
    return m_mousePosition;
}

bool InputHandler::getMouseButtonState(int buttonNumber){
    return m_mouseButtonStates[buttonNumber];
}

void InputHandler::updateMousePosition(SDL_Event &event){
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event &event){
    switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            m_mouseButtonStates[LEFT]= true;
            break;
            
        case SDL_BUTTON_MIDDLE:
            m_mouseButtonStates[MIDDLE] = true;
            break;
            
        case SDL_BUTTON_RIGHT:
            m_mouseButtonStates[RIGHT] = true;
            
        default:
            break;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event &event){
    switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            m_mouseButtonStates[LEFT]= false;
            break;
            
        case SDL_BUTTON_MIDDLE:
            m_mouseButtonStates[MIDDLE] = false;
            break;
            
        case SDL_BUTTON_RIGHT:
            m_mouseButtonStates[RIGHT] = false;
            
        default:
            break;
    }
}


//Gamepad/Joystick handling
void InputHandler::initializeJoysticks(){
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0){
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }
    
//    if (SDL_WasInit(SDL_INIT_HAPTIC)==0){
//        SDL_InitSubSystem(SDL_INIT_HAPTIC);
//    }
//    
    
    if (SDL_NumJoysticks() > 0 ){
        for (int i = 0 ; i < SDL_NumJoysticks() ; i++){
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            
            if (joy){
                
                m_joysticks.push_back(joy);
                m_joystickValues.push_back
                (make_pair(new Vector2D(0,0), new Vector2D(0,0)));
                
                vector<bool> tempButtons;
                
                for (int j = 0; j < SDL_JoystickNumButtons(joy);j++){
                    tempButtons.push_back(false);
                }
                m_buttonStates.push_back(tempButtons);
                m_bJoystickInitialized = true;
            } else {
                cout << "Failed to init joystick: " << SDL_GetError() << endl;
            }
        }
        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialized = true;
        cout << "Initialized " << m_joysticks.size() << " joysticks\n";
    } else {
        cout << "No joysticks initialized\n";
        m_bJoysticksInitialized = false;
    }
}

double InputHandler::xvalue(int joy, int stick){
    if (m_joystickValues.size() > 0 ){
        if (stick == 1){
            return m_joystickValues[joy].first->getX();
        }
        
        if (stick == 2){
            return m_joystickValues[joy].second->getX();
        }
    }
    return 0;
}

void InputHandler::printJoyStats(int joy){
    for (int i = 0 ; i < 15 ;i++){
        cout << "Button " << i << ": " << getButtonState(0, i) << endl;
    }
}


double InputHandler::yvalue(int joy, int stick){
    if (m_joystickValues.size() > 0 ){
        if (stick == 1){
            return m_joystickValues[joy].first->getY();
        }
        
        if (stick == 2){
            return m_joystickValues[joy].second->getY();
        }
    }
    return 0;
}

bool InputHandler::getButtonState(int joy, int buttonNumber){
    if (m_bJoystickInitialized){
        return m_buttonStates[joy][buttonNumber];
    }
    return 0;
}

void InputHandler::onJoystickButtonDown(SDL_Event &event){
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event &event){
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = false;
    
}

void InputHandler::onJoystickMotion(SDL_Event &event){
    
    int whichOne = event.jaxis.which;
    
    if (event.jaxis.axis == STICK_ONE_HORIZONTAL){
        if (event.jaxis.value > m_joystickDeadZone){
            m_joystickValues[whichOne].first->setX(1);
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setX(-1);
        } else {
            m_joystickValues[whichOne].first->setX(0);
        }
    }
    
    if (event.jaxis.axis == STICK_ONE_VERTICAL){
        if (event.jaxis.value > m_joystickDeadZone){
            m_joystickValues[whichOne].first->setY(1);
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setY(-1);
        } else {
            m_joystickValues[whichOne].first->setY(0);
        }
    }
    
    if (event.jaxis.axis == STICK_TWO_HORIZONTAL){
        if (event.jaxis.value > m_joystickDeadZone){
            m_joystickValues[whichOne].first->setX(1);
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setX(-1);
        } else {
            m_joystickValues[whichOne].second->setX(0);
        }
    }
    
    if (event.jaxis.axis == STICK_TWO_VERTICAL){
        if (event.jaxis.value > m_joystickDeadZone){
            m_joystickValues[whichOne].first->setX(1);
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setY(-1);
        } else {
            m_joystickValues[whichOne].second->setY(0);
        }
    }
    
}



int InputHandler::rumbleJoystick(){
//    //Try to init haptic
//    SDL_HapticEffect effect;
//    int effect_id;
//    
//    cout << "Attempting haptic!!\n";
//
//    // Open the device
//    SDL_Haptic* haptic = SDL_HapticOpenFromJoystick( m_joysticks[0] );
//    
//    if (haptic == NULL) {
//        cout << "No haptic feedback!\n";
//        return -1; // Most likely joystick isn't haptic
//    }
//    
//    // See if it can do sine waves
//    if ((SDL_HapticQuery(haptic) & SDL_HAPTIC_SINE)==0) {
//        SDL_HapticClose(haptic); // No sine effect
//        cout << "No sine haptic!\n";
//        return -1;
//    }
//    
//    // Create the effect
//    memset( &effect, 0, sizeof(SDL_HapticEffect) ); // 0 is safe default
//    effect.type = SDL_HAPTIC_DAMPER;
//    effect.periodic.direction.type = SDL_HAPTIC_POLAR; // Polar coordinates
//    effect.periodic.direction.dir[0] = 18000; // Force comes from south
//    effect.periodic.period = 1000; // 1000 ms
//    effect.periodic.magnitude = 20000; // 20000/32767 strength
//    effect.periodic.length = 5000; // 5 seconds long
//    effect.periodic.attack_length = 1000; // Takes 1 second to get max strength
//    effect.periodic.fade_length = 1000; // Takes 1 second to fade away
//    
//    // Upload the effect
//    effect_id = SDL_HapticNewEffect( haptic, &effect );
//    
//    // Test the effect
//    SDL_HapticRunEffect( haptic, effect_id, 2 );
//
//    SDL_HapticDestroyEffect(haptic, effect_id);
    return 0;
}












































































//END