//
//  AnimatedGraphic.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__AnimatedGraphic__
#define __SDLGameDevelopmentChapter1__AnimatedGraphic__

#include <iostream>
#include "SDLGameObject.h"
#include "GameObjectFactory.h"


//inherit from sdlgameobject
class AnimatedGraphic : public SDLGameObject {
public:
    AnimatedGraphic();
    AnimatedGraphic
    (GameObjectParams params, int totalFrames , int animSpeed);
    
    void load(GameObjectParams params);
    void draw();
    void update();
    void clean();
    void collision();
};


class AnimatedGraphicCreator : public IBaseCreator{
    IGameObject* createGameObject() const final {
        return new AnimatedGraphic();
    }
};




#endif /* defined(__SDLGameDevelopmentChapter1__AnimatedGraphic__) */






















































//END