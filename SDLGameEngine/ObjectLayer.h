//
//  ObjectLayer.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/24/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__ObjectLayer__
#define __SDLGameDevelopmentChapter1__ObjectLayer__

#include <iostream>
#include <vector>
#include "Layer.h"
#include "GameObject.h"

using namespace std;


class ObjectLayer : public Layer{
public:
    virtual void update(Level* pLevel);
    virtual void render();
    virtual void clean();
    
    vector<GameObject*>* getGameObjects(){
        return &m_gameObjects;
    }

private:
    vector<GameObject*> m_gameObjects;
    
    SDL_Color currentShade{80,80,80};
};


#endif /* defined(__SDLGameDevelopmentChapter1__ObjectLayer__) */
