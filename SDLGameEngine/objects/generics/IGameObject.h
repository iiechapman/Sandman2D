//
//  IGameObject.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__GameObject__
#define __SDLGameDevelopmentChapter1__GameObject__

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "TextureManager.h"
#include "GameObjectParams.h"

using namespace std;

class IGameObject{
public:
    IGameObject(GameObjectParams params);
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
    
    virtual void load(GameObjectParams) = 0;
    
    GameObjectParams& GetParams();
    
protected:
    IGameObject();
    virtual ~IGameObject();
    
    GameObjectParams m_params;
    
};


#endif /* defined(__SDLGameDevelopmentChapter1__GameObject__) */






















































//END