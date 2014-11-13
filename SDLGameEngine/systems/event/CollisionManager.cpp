//  CollisionManager.cpp
//  SDLGameDevelopmentChapter1
// Created by Evan Chapman on 7/8/14.
// Copyright (c) 2014 Evan Chapman. All rights reserved.

#include "CollisionManager.h"
#include "Player.h"
#include "Camera.h"
#include "TileLayer.h"
#include <vector>

CollisionManager::CollisionManager() {
    // New Collision manager
}

CollisionManager::~CollisionManager() {
    // Clean up collision manager
    // updating
}
CollisionManager* CollisionManager::s_pInstance = 0;

CollisionManager* CollisionManager::Instance() {
    if (!s_pInstance) {
        s_pInstance = new CollisionManager();
    }
    return s_pInstance;
}
// This function needs to be broken down into smaller pieces
void CollisionManager::checkPlayerTileCollision
(Player* pPlayer, const vector<TileLayer*> &collisionLayers) {
    // Iterate through all collision layers

    for (vector<TileLayer*>::const_iterator it = collisionLayers.begin();
         it != collisionLayers.end() ; it++) {
        // Grab current tilelayer
        TileLayer* pTileLayer = (*it);
        // Grab current tiles
        vector<vector<int>> tiles = pTileLayer->getTileIDs();

        // Get layers position
        Vector2D<double> layerPos = pTileLayer->getPosition();

        // Calculate position on tile map
        double x = 0, y = 0;
        x = ((layerPos.getX()) / pTileLayer->getTileSize());
        y = ((layerPos.getY()) / pTileLayer->getTileSize());
        // If moving upwards or rightwards
        double tileColumn = 0, tileRow = 0, tileID = 0;
        if (pPlayer->GetParams().getVelocity().getX() > 0.0f ||
            pPlayer->GetParams().getVelocity().getY() > 0.0f ) {
            tileColumn = ((((pPlayer->GetParams().getX()) +
                            Camera::Instance()->getPosition().getX() +
                           pPlayer->GetParams().getWidth()) /
                           pTileLayer->getTileSize()));

            tileRow = (((pPlayer->GetParams().getY() +
                         Camera::Instance()->getPosition().getY() +
                        pPlayer->GetParams().getHeight()) /
                        pTileLayer->getTileSize()));

            // Check tile bounds
            // cout << pTileLayer->getNumColumns() << "\n";
            if ((tileRow + y )< pTileLayer->getNumRows() &&
                (tileColumn + x) < pTileLayer->getNumColumns()) {
                tileID = tiles[tileRow + y][tileColumn + x];
            } else {
                tileID = 0;
            }

            // If moving downwards or leftwards
            // Change to get params new method "Moving Down
        } else if (pPlayer->GetParams().getVelocity().getX() < 0.0f ||
                   pPlayer->GetParams().getVelocity().getY() < 0.0f ) {
            // Get Current TileColum
            tileColumn = ((pPlayer->GetParams().getX() +
                            Camera::Instance()->getPosition().getX())
                          / pTileLayer->getTileSize());

            tileRow = ((pPlayer->GetParams().getY() +
                       Camera::Instance()->getPosition().getY())
                       / pTileLayer->getTileSize());

            // Check tile bounds
            // cout << pTileLayer->getNumColumns() << "\n";

            if ((tileRow + y ) > 0 &&
                (tileColumn + x) > 0) {
                tileID = tiles[tileRow + y][tileColumn + x];
            } else {
                tileID = 0;
            }
        }
        // If tileID is not blank, collision occured
        if ( tileID != 0 ) {
            pPlayer->collision();
        }
    }
}


void CollisionManager::setCollisionLayers(vector<TileLayer*> collisionLayers) {
    m_pCollisionLayers = collisionLayers;
}

vector<TileLayer*>* CollisionManager::getCollisionLayers() {
    return &m_pCollisionLayers;
}















































// END