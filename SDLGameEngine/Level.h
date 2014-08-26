//
//  Level.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__Level__
#define __SDLGameDevelopmentChapter1__Level__

#include <iostream>
#include <string>
#include <vector>
#include "Layer.h"
#include "Player.h"
#include "LevelParser.h"
#include "Event.h"
#include "CollisionManager.h"
#include "TileSet.h"

using namespace std;


class TileLayer;

class Level{
public:
    ~Level();
    
    void update();
    void render();
    void clean();
    
    void setPlayer(Player* player){
        m_Player = player;
        CollisionManager::Instance()->setCollisionLayers(m_collisionLayers);
        cout << "Player set for level\n";
    }
    Player* getPlayer(){
        return m_Player;
    }
    
    vector<Tileset>* getTilesets();
    vector<Layer*>* getLayers();
    
    vector<TileLayer*>* getCollisionLayers();
    const vector<TileLayer*>* getCollidableLayers();
    
private:
    friend class LevelParser;
    Level();
    
    void checkCollisions();
    
    vector<Tileset> m_tilesets;
    vector<Layer*> m_layers;
    vector<TileLayer*> m_collisionLayers;
    
    Player* m_Player;
    
    friend class LevelParser;
};


#endif /* defined(__SDLGameDevelopmentChapter1__Level__) */





















































//END