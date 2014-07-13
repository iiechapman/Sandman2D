//
//  TileLayer.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "TileLayer.h"
#include "Game.h"
#include "Camera.h"

void TileLayer::render(){
    int x, y, x2, y2 = 0;
    
    //Calculate left/top coord
    x = m_position.getX() / m_tileSize;
    y = m_position.getY() / m_tileSize;
    
    //Calculate right/bottom coord
    x2 = int(m_position.getX()) % m_tileSize;
    y2 = int(m_position.getY()) % m_tileSize;
    
    
    for (int i = 0 ; i < m_numRows; i++){
        for (int j = 0 ; j < m_numColumns; j++){
            
            int id = m_tileIDs[i][j+x];
            
            if (id == 0){
                continue;
            }
            
            //Check if tile is outside of viewable area
            if (((j * m_tileSize) - x2)
                - Camera::Instance()->getPosition().getX() <-m_tileSize ||
                ((j * m_tileSize - x2 - Camera::Instance()->getPosition().getX()
                     > Game::Instance()->getGameWidth()))){
                continue;
            }
            
            Tileset tileset = getTilesetByID(id);
            id--;
        
            //Drawtile, offset by camera
            TextureManager::Instance()->drawTile
            (tileset.name, tileset.margin, tileset.spacing,
             (((j * m_tileSize) - x2) - Camera::Instance()->getPosition().getX()),
             (((i * m_tileSize) - y2) - Camera::Instance()->getPosition().getY()),
             (m_tileSize), (m_tileSize),
             (id - (tileset.firstGridID - 1)) / tileset.numColumns,
             (id - (tileset.firstGridID - 1)) % tileset.numColumns,
             Game::Instance()->getZoom(),Game::Instance()->getRenderer());
        }
    }
}

void TileLayer::update(Level* pLevel){
//    m_position += m_velocity;
//    m_velocity.setX(1);
}

TileLayer::TileLayer(int tileSize,int mapWidth, int mapHeight, const vector<Tileset> &tilesets)
:m_tileSize(tileSize) , m_tilesets(tilesets),m_position(0,0), m_velocity(0,0)
{
    m_mapWidth = mapWidth;
    m_mapHeight = mapHeight;
    m_numColumns = mapWidth;
    m_numRows = mapHeight;
    Game::Instance()->setMapHeight(mapHeight * tileSize);
    Game::Instance()->setMapWidth(mapWidth * tileSize);
}

Tileset TileLayer::getTilesetByID(int tileID){
    for (int i = 0; i < m_tilesets.size() ; i++){
        if (i + 1 <=m_tilesets.size() - 1){
            if (tileID >= m_tilesets[i].firstGridID &&
                tileID < m_tilesets[i+1].firstGridID){
                return m_tilesets[i];
            }
        } else {
            return m_tilesets[i];
        }
    }
    
    cout << "Did not find tileset, returning empty tileset\n";
    Tileset t;
    return t;
}





































































//END