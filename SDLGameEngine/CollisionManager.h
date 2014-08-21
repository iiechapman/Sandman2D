//
//  CollisionManager.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 7/8/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__CollisionManager__
#define __SDLGameDevelopmentChapter1__CollisionManager__

#include <iostream>
#include <vector>

class TileLayer;
class Player;

using namespace std;


class CollisionManager{
public:
    ~CollisionManager();
    
    static CollisionManager* Instance();
    
    void checkPlayerTileCollision
    (Player* pPlayer, const vector<TileLayer*> &collisionLayers);

    void setCollisionLayers(vector<TileLayer*> collisionLayers);
    
    vector<TileLayer*>* getCollisionLayers();
    
private:
    CollisionManager();
    
    static CollisionManager* s_pInstance;
    const double m_Buffer = 2;
    
    vector<TileLayer*> m_pCollisionLayers;
    
    
};




#endif /* defined(__SDLGameDevelopmentChapter1__CollisionManager__) */
