//
//  MenuButton.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 5/11/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__MenuButton__
#define __SDLGameDevelopmentChapter1__MenuButton__

#include <iostream>
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"

class MenuButton : public SDLGameObject{
public:
    MenuButton();
    
    virtual void setCallback(void(*callback)()) {m_callback = callback;}
    
    virtual void load(GameObjectParams params);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void collision();
    
    int getCallbackID() { return GetParams().getCallbackID();}
    
private:
    enum button_state{
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        MOUSE_CLICKED = 2
    };
    
    void (*m_callback)();
    bool m_bReleased;
    
};


class MenuButtonCreator : public BaseCreator{
    
    GameObject* createGameObject() const {
        return new MenuButton();
    }
};

#endif /* defined(__SDLGameDevelopmentChapter1__MenuButton__) */
