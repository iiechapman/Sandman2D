//
//  CollisionHandler.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 7/7/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "CollisionHandler.h"


bool CollisionHandler::checkCollision(GameObject *p1, GameObject *p2){
    double leftA,leftB;
    double rightA,rightB;
    double topA, topB;
    double bottomA,bottomB;
    
    leftA = p1->GetParams().getPosition().getX() + 10;
    leftB = p2->GetParams().getPosition().getX() + 10;
    
    rightA = p1->GetParams().getPosition().getX() - 10 + p1->GetParams().getWidth();
    rightB = p2->GetParams().getPosition().getX() - 10 + p2->GetParams().getWidth();
    
    topA = p1->GetParams().getPosition().getY() + 10;
    topB = p2->GetParams().getPosition().getY() + 10;
    
    bottomA = p1->GetParams().getPosition().getY() - 10 + p1->GetParams().getHeight();
    bottomB = p2->GetParams().getPosition().getY() - 10 + p2->GetParams().getHeight();
    
    //If any sides outside, no collision occured
    if (leftA >= rightB) { return false;}
    if (rightA <= leftB) { return false;}
    if (topA > bottomB) { return false;}
    if (bottomA  <= topB) { return false;}
    
    
    return true;
}
