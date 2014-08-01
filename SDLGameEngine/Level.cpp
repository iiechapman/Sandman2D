//
//  Level.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "Level.h"
#include "Layer.h"

vector<Tileset>* Level::getTilesets(){
    return &m_tilesets;
}

vector<Layer*>* Level::getLayers(){
    return &m_layers;
}

const vector<TileLayer*>* Level::getCollidableLayers(){
    return &m_collisionLayers;
}

vector<TileLayer*>* Level::getCollisionLayers(){
    return &m_collisionLayers;
}

Level::Level(){
    //Created level
}

void Level::render(){
    for (int i = 0 ; i < m_layers.size() ; i++){
        m_layers[i]->render();
    }
}

void Level::update(){
    for (int i = 0 ; i <m_layers.size() ;i++){
        m_layers[i]->update(this);
    }
}

void Level::clean(){
    while (!m_layers.empty()) {
        m_layers.back()->clean();
        m_layers.pop_back();
    }
}