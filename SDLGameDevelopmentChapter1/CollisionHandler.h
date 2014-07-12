//
//  CollisionHandler.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 7/7/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__CollisionHandler__
#define __SDLGameDevelopmentChapter1__CollisionHandler__

#include <iostream>
#include "GameObject.h"

class CollisionHandler{
public:
    static bool checkCollision(GameObject *p1, GameObject *p2);
    
};



#endif /* defined(__SDLGameDevelopmentChapter1__CollisionHandler__) */
