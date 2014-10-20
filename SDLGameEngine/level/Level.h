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
#include "ILayer.h"
#include "Player.h"
#include "LevelParser.h"
#include "Event.h"
#include "CollisionManager.h"
#include "TileSet.h"

using namespace std;

class TileLayer;

/**
 * \class Level
 * \brief Handles level
 * \note Needs cleanup
 * \author Evan Chapman
 * \version 1
 * Contact: iiechapman\@gmail.com
 */
class Level{
public:
    ~Level();
    
    void update();
    void render();
    void clean();
    
    void setPlayer(Player* player);
    
    Player* getPlayer();
    
    vector<Tileset>* getTilesets();
    vector<ILayer*>* getLayers();
    
    vector<TileLayer*>* getCollisionLayers();
    const vector<TileLayer*>* getCollidableLayers();
    
private:
    /**< Used to allow LevelParser access to Level attributes */
    friend class LevelParser;
    Level();
    
    void checkCollisions();
    
    vector<Tileset> m_tilesets;
    vector<ILayer*> m_layers;
    vector<TileLayer*> m_collisionLayers;
    
    Player* m_Player;
    
    friend class LevelParser;
};


#endif /* defined(__SDLGameDevelopmentChapter1__Level__) */





















































//END