//
//  Light.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__Light__
#define __SDLGameDevelopmentChapter1__Light__

#include <iostream>
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

//inherit from sdlgameobject
class Light : public SDLGameObject {
public:
    Light();
    Light(GameObjectParams params , int numberFrames);
    void load(GameObjectParams params);
    void draw();
    void update();
    void clean();
    virtual void collision();
    
};


class LightCreator : public BaseCreator{
    GameObject* createGameObject() const {
        return new Light();
    }
};

#endif /* defined(__SDLGameDevelopmentChapter1__Light__) */
