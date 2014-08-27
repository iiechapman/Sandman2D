
//
//  TileLayer.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <cmath>
#include "TileLayer.h"
#include "Game.h"
#include "Camera.h"

using namespace std;

void TileLayer::render(){
    double x, x2, y2 = 0;
    
    //Calculate left/top coord
    x = m_position.getX() / m_tileSize;
    
    //Calculate right/bottom coord
    x2 = fmod(m_position.getX(), double(m_tileSize));
    y2 = fmod(m_position.getY(), double(m_tileSize));
    
    //Parse through each column and row
    for (int i = 0 ; i < m_numRows; i++){
        for (int j = 0 ; j < m_numColumns; j++){
            
            int id = m_tileIDs[i][j+x];
            
            if (id == 0){
                continue;
            }
            
            //Check if tile is outside of viewable area
            if (
                ((j * m_tileSize) - x2)
                - Camera::Instance()->getPosition().getX() < -m_tileSize ||
                ((j * m_tileSize - x2) - Camera::Instance()->getPosition().getX()
                 > Game::Instance()->getGameWidth() -m_tileSize
                 *Game::Instance()->getGlobalZoom()) ||
                
                ((i * m_tileSize) - y2) - Camera::Instance()->getPosition().getY() < -m_tileSize ||
                ((i * m_tileSize - y2) - Camera::Instance()->getPosition().getY()) >
                Game::Instance()->getGameHeight() + m_tileSize * Game::Instance()->getGlobalZoom())
            {
                continue;
            }
            
            Tileset tileset = getTilesetByID(id);
            id--;
            
            //Drawtile, offset by camera
            TextureManager::Instance()->drawTile
            (tileset.name, tileset.margin, tileset.spacing,
             (((j * m_tileSize) - x2)),
             (((i * m_tileSize) - y2)),
             (m_tileSize), (m_tileSize),
             (id - (tileset.firstGridID - 1)) / tileset.numColumns,
             (id - (tileset.firstGridID - 1)) % tileset.numColumns,
             Game::Instance()->getGlobalZoom(),Game::Instance()->getRenderer());
        }
    }
}

void TileLayer::update(Level* pLevel){
    
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
        if (i + 1 <= m_tilesets.size() - 1){
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

void TileLayer::clean(){
    //TODO: Fill this in and clean
}

void TileLayer::setTileIDs(const vector<vector<int>>& data){
    m_tileIDs = data;
}
void TileLayer::setTileSize(int tileSize){
    m_tileSize = tileSize;
}
void TileLayer::setNumColumns(int numColumns){
    m_numColumns = numColumns;
}
void TileLayer::setNumRows(int numRows){
    m_numRows = numRows;
}

vector<vector<int>> TileLayer::getTileIDs(){
    return m_tileIDs;
};

Vector2D<double> TileLayer::getPosition(){
    return m_position;
}
Vector2D<double> TileLayer::getVelocity(){
    return m_velocity;
}

int TileLayer::getTileSize(){
    return m_tileSize;
}
int TileLayer::getNumColumns(){
    return m_numColumns;
}
int TileLayer::getNumRows(){
    return m_numRows;
}




















































//END
