//
//  TileSet.h
//  SDLGameEngine
//
//  Created by Evan Chapman on 8/21/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef SDLGameEngine_TileSet_h
#define SDLGameEngine_TileSet_h


struct Tileset{
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    string name;
};


#endif
