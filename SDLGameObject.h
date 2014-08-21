//
//  SDLGameObject.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/30/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__SDLGameObject__
#define __SDLGameDevelopmentChapter1__SDLGameObject__

#include <iostream>
#include "GameObject.h"

class SDLGameObject : public GameObject{
public:
    SDLGameObject();
    SDLGameObject(GameObjectParams params);
    ~SDLGameObject();
    
    virtual void load(GameObjectParams params);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void collision();
    bool checkCollideWithTile(Vector2D<double> pos);
    
};

#endif /* defined(__SDLGameDevelopmentChapter1__SDLGameObject__) */
