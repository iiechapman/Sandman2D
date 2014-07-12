//
//  CollisionHandler.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 7/7/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "CollisionHandler.h"


bool CollisionHandler::checkCollision(GameObject *p1, GameObject *p2){
    int leftA,leftB;
    int rightA,rightB;
    int topA, topB;
    int bottomA,bottomB;
    
    leftA = p1->GetParams().getPosition().getX();
    leftB = p2->GetParams().getPosition().getX();
    
    rightA = p1->GetParams().getPosition().getX() + p1->GetParams().getWidth();
    rightB = p2->GetParams().getPosition().getX() + p2->GetParams().getWidth();
    
    topA = p1->GetParams().getPosition().getY();
    topB = p2->GetParams().getPosition().getY();
    
    bottomA = p1->GetParams().getPosition().getY() + p1->GetParams().getHeight();
    bottomB = p2->GetParams().getPosition().getY() + p2->GetParams().getHeight();
    
    //If any sides outside, no collision occured
    if (leftA >= rightB) { return false;}
    if (rightA <= leftB) { return false;}
    if (topA > bottomB) { return false;}
    if (bottomA  <= topB) { return false;}
    
    
    return true;
}
