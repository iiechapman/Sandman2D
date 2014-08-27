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
#include <vector>
#include "ILayer.h"
#include "TileSet.h"
#include "Vector2D.h"

using namespace std;

class Level;

/**
 * \class TileLayer
 * \brief Layer of tiles, handles tilemaps
 * \note Inherits from Layer interface
 * \author Evan Chapman
 * \version 1
 * Contact: iiechapman\@gmail.com
 */
class TileLayer : public ILayer{
public:
    //Used to allow CollisionManager to test objects against tiles
    friend class CollisionManager;
    
    TileLayer(int tileSize,int mapWidth, int mapHeight, const vector<Tileset> &tilesets);
    
    void update(Level* pLevel);
    void render();
    void clean();
    
    /*! \fn setTileIDs;
     *  \brief Populates each cell with int data loaded from a file
     *  \param Takes a preloaded vectory array
     */
    void setTileIDs(const vector<vector<int>>& data);
    void setTileSize(int tileSize);
    void setNumColumns(int numColumns);
    void setNumRows(int numRows);
    
    Tileset getTilesetByID(int tileID);
    
    vector<vector<int>> getTileIDs();
    
    Vector2D<double> getPosition();
    Vector2D<double> getVelocity();
    
    int getTileSize();
    int getNumColumns();
    int getNumRows();
    
private:
    int m_numColumns;
    int m_numRows;
    int m_tileSize;
    int m_mapWidth;
    int m_mapHeight;
    
    Vector2D<double> m_position;
    Vector2D<double> m_velocity;
    
    const vector<Tileset> &m_tilesets;
    vector<vector<int>> m_tileIDs;
};
























#endif /* defined(__SDLGameDevelopmentChapter1__TileLayer__) */
