//
//  InputHandler.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __LudumDare29__InputHandler__
#define __LudumDare29__InputHandler__



#include <iostream>
#include <vector>
#include "ControllerConfig.h"
#include "GameObjectParams.h"

using namespace std;

enum mouse_buttons{
    LEFT    = 0,
    MIDDLE  = 1,
    RIGHT   = 2
};

class InputHandler{
public:
    ~InputHandler();
    
    static InputHandler* Instance();
    
    void update();
    void reset();
    void clean();
    
    //Keyboard Handling
    bool isKeyDown(SDL_Scancode key) const;
    
    //Mouse Handling
    Vector2D* getMousePosition();
    bool getMouseButtonState(int buttonNumber);

    //Gamepad/Joystick Handling
    void initializeJoysticks();
    bool joysticksInitialized();
    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);
    bool getButtonState(int joy, int buttonNumber); 

private:
    InputHandler();
    static InputHandler* s_pInstance;
    
    //Keyboard handling
    void updateKeys();
    const Uint8* m_keystates;
    
    //Mouse handling
    void onMouseButtonDown(SDL_Event &event);
    void onMouseButtonUp(SDL_Event &event);
    
    void updateMousePosition(SDL_Event &event);
    Vector2D* m_mousePosition;
    vector<bool>m_mouseButtonStates;
    
    //Gamepad/Joystick handling
    void onJoystickButtonDown(SDL_Event &event);
    void onJoystickButtonUp(SDL_Event &event);
    void onJoystickMotion(SDL_Event &event);
    
    vector<SDL_Joystick*> m_joysticks;
    vector<pair<Vector2D*, Vector2D*>> m_joystickValues;
    bool m_bJoysticksInitialized;
    const int m_joystickDeadZone = 10000;
    vector<vector<bool>> m_buttonStates;
    
    
};



#endif /* defined(__LudumDare29__InputHandler__) */







































































//END