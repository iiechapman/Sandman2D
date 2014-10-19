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
#include "ILayer.h"
#include "IGameObject.h"

using namespace std;

/**
 * \class ObjectLayer
 * \brief Layer of objects ie lights, items, players
 * \note Inherits from Layer
 * \author Evan Chapman
 * \version 1
 * Contact: iiechapman\@gmail.com
 */
class ObjectLayer : public ILayer{
public:
    virtual void update(Level* pLevel);
    virtual void render();
    virtual void clean();
    
    vector<IGameObject*>* getGameObjects();

private:
    vector<IGameObject*> m_gameObjects;
    
    /**< Used to control darkness rendered on to layer */
    SDL_Color currentShade{100,100,100};
};


#endif /* defined(__SDLGameDevelopmentChapter1__ObjectLayer__) */






















































//END