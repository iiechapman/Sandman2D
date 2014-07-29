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
class Layer;
class TileLayer;
class PlayState;

using namespace std;


class LevelParser{
public:
    
    Level* parseLevel(const char* levelFile , PlayState* newState);
    
private:
    
    void parseTilesets
    (TiXmlElement* pTileSetRoot, vector<Tileset>* pTilesets);
    
    void parseTileLayer
    (TiXmlElement* pTileElement, vector<Layer*>* pLayers,
    vector<TileLayer*>* pCollisionLayers, vector<Tileset>* pTilesets);
    
    void parseLibrary(const char* fileName);
    void parseTextures(TiXmlElement* pTextureRoot);
    void parseSongs(TiXmlElement* pSongRoot);
    void parseSounds(TiXmlElement* pSoundRoot);
    
    void parseObjectLayer
    (TiXmlElement* pObjectElement, vector<Layer*>* pLayers,string type, Level* pLevel);
    
    TiXmlElement* findElement(string element,TiXmlElement* root);
    
    int m_tileSize;
    int m_width;
    int m_height;
};




#endif /* defined(__SDLGameDevelopmentChapter1__LevelParser__) */







































































//END