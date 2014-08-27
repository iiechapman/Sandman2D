//
//  LevelParser.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__LevelParser__
#define __SDLGameDevelopmentChapter1__LevelParser__

#include <iostream>
#include <vector>
#include "tinyxml.h"


class Level;
struct Tileset;
class ILayer;
class TileLayer;
class PlayState;

using namespace std;

/**
 * \class LevelParser
 * \brief Handles reading the TMX and XML files to load assetts
 * \note Can be broadened in later versions
 * \author Evan Chapman
 * \version 1
 * Contact: iiechapman\@gmail.com
 */
class LevelParser{
public:
    LevelParser();
    Level* parseLevel(const char* levelFile , PlayState* newState);
    
private:
    void parseTilesets
    (TiXmlElement* pTileSetRoot, vector<Tileset>* pTilesets);
    
    void parseTileLayer
    (TiXmlElement* pTileElement, vector<ILayer*>* pLayers,
    vector<TileLayer*>* pCollisionLayers, vector<Tileset>* pTilesets);
    
    void parseTextures(TiXmlElement* pTextureRoot);
    
    void parseObjectLayer
    (TiXmlElement* pObjectElement, vector<ILayer*>* pLayers,string type, Level* pLevel,PlayState* newState);
    
    TiXmlElement* findElement(string element,TiXmlElement* root);
    
    int m_tileSize;
    int m_width;
    int m_height;
};




#endif /* defined(__SDLGameDevelopmentChapter1__LevelParser__) */







































































//END