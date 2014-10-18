//
//  Enemy.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__Enemy__
#define __SDLGameDevelopmentChapter1__Enemy__

#include <iostream>
#include "SDLGameObject.h"
#include "GameObjectFactory.h"
#include "EventHandler.h"
#include "Event.h"

//inherit from sdlgameobject
class Enemy : public SDLGameObject {
public:
    Enemy();
    Enemy(GameObjectParams params , int numberFrames);
    void load(GameObjectParams params);
    void draw();
    void update();
    void clean();
    virtual void collision();
    
    
private:


};


class EnemyCreator : public IBaseCreator{
    IGameObject* createGameObject() const {
        return new Enemy();
    }
};

#endif /* defined(__SDLGameDevelopmentChapter1__Enemy__) */






















































//END