//
//  CollisionManager.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 7/8/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "CollisionManager.h"
#include "Player.h"
#include "Game.h"

CollisionManager::CollisionManager(){
    //New Collision manager
}

CollisionManager* CollisionManager::s_pInstance = 0;

CollisionManager::~CollisionManager(){
    //Clean up collision manager
    //updating
}

CollisionManager* CollisionManager::Instance(){
    if (!s_pInstance){
        s_pInstance = new CollisionManager();
    }
    
    return s_pInstance;
}

void CollisionManager::checkPlayerTileCollision
(Player* pPlayer, const vector<TileLayer*> &collisionLayers){

    //Iterate through all collision layers
    
    for (vector<TileLayer*>::const_iterator it = collisionLayers.begin();
         it != collisionLayers.end() ; it++){
        
        TileLayer* pTileLayer = (*it);
        vector<vector<int>> tiles = pTileLayer->getTileIDs();
        
        //Get layers position
        Vector2D layerPos = pTileLayer->getPosition();

        int x,y,tileColumn,tileRow,tileID = 0;
        
        //Calculate position on tile map
        x = (layerPos.getX()) / pTileLayer->getTileSize();
        y = (layerPos.getY()) / pTileLayer->getTileSize();
    
        
        //If moving upwards or rightwards
        if (pPlayer->GetParams().getVelocity().getX() > 0.0f ||
            pPlayer->GetParams().getVelocity().getY() > 0.0f ){
            
            tileColumn = ((((pPlayer->GetParams().getX()) +
                           pPlayer->GetParams().getWidth()) / pTileLayer->getTileSize())/ Game::Instance()->getZoom());
            
            tileRow = (((pPlayer->GetParams().getY() +
                        pPlayer->GetParams().getHeight()) / pTileLayer->getTileSize())/ Game::Instance()->getZoom());
            
            tileID = tiles[tileRow + y][tileColumn + x];
            
            
            //If moving downwards or leftwards
        } else if (pPlayer->GetParams().getVelocity().getX() < 0.0f ||
                   pPlayer->GetParams().getVelocity().getY() < 0.0f ){
            
            tileColumn = (((pPlayer->GetParams().getX() / pTileLayer->getTileSize())/ Game::Instance()->getZoom()));
            
            tileRow = (((pPlayer->GetParams().getY() / pTileLayer->getTileSize())/ Game::Instance()->getZoom()));
            
            tileID = tiles[tileRow + y][tileColumn + x];
        }
        //If tileID is not blank, collision occured
        if (tileID != 0 ){
            pPlayer->collision();
        }
    }
}









































































//ENDs