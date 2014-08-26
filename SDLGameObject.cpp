//
//  SDLGameObject.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/30/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <string>
#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "CollisionManager.h"
#include "TileLayer.h"

SDLGameObject::SDLGameObject()
:GameObject(){
}

SDLGameObject::SDLGameObject(GameObjectParams params)
:GameObject(params){
}

void SDLGameObject::load(GameObjectParams params){
    //cout << "Loading Params\n";
    m_params = params;
}

SDLGameObject::~SDLGameObject(){
    cout << "Deleted SDLGame Object\n";
}

void SDLGameObject::draw(){
    //Old draw method, animate and flip left and right depending on velocity
    if (GetParams().dirRight()){
        TextureManager::Instance()->
        drawFrame(&m_params, Game::Instance()->getRenderer(),
                  SDL_FLIP_NONE,Game::Instance()->getGlobalZoom());
    } else {
        TextureManager::Instance()->
        drawFrame(&m_params, Game::Instance()->getRenderer(),
                  SDL_FLIP_HORIZONTAL,Game::Instance()->getGlobalZoom());
    }
}

void SDLGameObject::update(){

}

void SDLGameObject::clean(){
    //Perform any cleanup
}

void SDLGameObject::collision(){
    //Handle collision
    cout << "Collision detected\n";
    
}

bool SDLGameObject::checkCollideWithTile(Vector2D<double> pos){
    
    //Iterate through all collision layers
    for (vector<TileLayer*>::const_iterator it
         = CollisionManager::Instance()->getCollisionLayers()->begin();
         it !=  CollisionManager::Instance()->getCollisionLayers()->end() ; it++){
        
        TileLayer* pTileLayer = (*it);
        vector<vector<int>> tiles = pTileLayer->getTileIDs();
        
        //Get layers position
        //Vector2D layerPos = pTileLayer->getPosition();
        Vector2D<double> layerPos
        (pTileLayer->getPosition().getX(),
         pTileLayer->getPosition().getY());
        
        double x,y,tileColumn,tileRow,tileID = 0;
        
        //Calculate position on tile map
        x = ((layerPos.getX()) / pTileLayer->getTileSize());
        y = ((layerPos.getY()) / pTileLayer->getTileSize());
        
        //New collision detection
        Vector2D<double> startPos = pos;
        
        startPos.setX(startPos.getX() + GetParams().getWidth()/4);
        startPos.setY(startPos.getY() + GetParams().getHeight()/4);
        
        Vector2D<double> endPos
        (pos.getX() + GetParams().getWidth() - GetParams().getWidth()/4,
         pos.getY() + GetParams().getHeight());
        
        
        for (int i = startPos.getX(); i < endPos.getX(); i++ ){
            for (int j = startPos.getY() ; j < endPos.getY() ; j++){
                tileColumn = i / pTileLayer->getTileSize();
                tileRow = j / pTileLayer->getTileSize();
                
                if (tileColumn + x >= Game::Instance()->getMapWidth() / pTileLayer->getTileSize() ||
                    tileColumn + x < 0){
                    tileID = 0;
                } else if (tileRow + y >= (Game::Instance()->getMapHeight() / pTileLayer->getTileSize()) ||
                           tileRow + y < 0){
                    tileID = 0;
                } else {
                    tileID = tiles[tileRow + y][tileColumn + x];
                }
                
                //If tileID is not blank, collision occured
                if (tileID != 0 ){
                    return true;
                }
            }
        }
    }
    return false;
}




































































//END