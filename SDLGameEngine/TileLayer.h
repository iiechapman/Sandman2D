//
//  TileLayer.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__TileLayer__
#define __SDLGameDevelopmentChapter1__TileLayer__

#include <iostream>
#include "Layer.h"
#include "Level.h"
#include "Vector2D.h"

using namespace std;

class TileLayer : public Layer{
public:
    
    TileLayer(int tileSize, const vector<Tileset> &tilesets);
    
    virtual void update(Level* pLevel);
    virtual void render();
    
    void setTileIDs(const vector<vector<int>>& data){
        m_tileIDs = data;
    }
    void setTileSize(int tileSize){
        m_tileSize = tileSize;
    }
    void setNumColumns(int numColumns){
        m_numColumns = numColumns;
    }
    void setNumRows(int numRows){
        m_numRows = numRows;
    }
    
    Tileset getTilesetByID(int tileID);
    
    vector<vector<int>> getTileIDs(){
        return m_tileIDs;
    };
    
    Vector2D getPosition(){
        return m_position;
    }
    Vector2D getVelocity(){
        return m_velocity;
    }
    
    int getTileSize(){
        return m_tileSize;
    }
    int getNumColumns(){
        return m_numColumns;
    }
    int getNumRows(){
        return m_numRows;
    }
    
private:
    
    int m_numColumns;
    int m_numRows;
    int m_tileSize;
    
    Vector2D m_position;
    Vector2D m_velocity;
    
    const vector<Tileset> &m_tilesets;
    vector<vector<int>> m_tileIDs;
    
};


#endif /* defined(__SDLGameDevelopmentChapter1__TileLayer__) */
