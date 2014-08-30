//
//  TextureManager.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/22/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__TextureManager__
#define __SDLGameDevelopmentChapter1__TextureManager__

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Vector2D.h"
#include "GameObjectParams.h"

using namespace std;

/**
 * \class TextureManager
 * \brief Handles all textures and rendering
 * \note
 * \author Evan Chapman
 * \version 1
 * Contact: iiechapman\@gmail.com
 */
class TextureManager{
public:
    ~TextureManager();
    static TextureManager* Instance();
    
    bool load(string fileName, string id, SDL_Renderer* pRenderer);
    
    void draw(string id, double x, double y,
              int width, int height,
              SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    void draw(string id, Vector2D<double> pos,
              int width, int height,
              SDL_Renderer* pRenderer, SDL_RendererFlip flip);

    
    void drawFrame(string id, double x, double y,
                   int width, int height,int currentRow, int currentFrame,
                   double zoom ,SDL_Renderer* pRenderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    void drawFrame(GameObjectParams* params,
                   SDL_Renderer* pRenderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE,
                   double zoom = 1.0);
    
    void drawFrame(string id, Vector2D<double> pos,
                   int width, int height,
                   int currentRow, int currentFrame,
                   SDL_Renderer* pRenderer, SDL_RendererFlip flip);
    
    void drawTile(string id, int margin, int spacing, double x,
                  double y, int width, int height,int currentRow,
                  int currentFrame, double zoom, SDL_Renderer* pRenderer);

    
    void clean();
    bool doesTextureExist(string id);
    void clearFromTextureMap(string id);
    
private:
    TextureManager(){};
    
    static TextureManager* s_pInstance;
    map<string, SDL_Texture*> m_textureMap;
    
};



#endif /* defined(__SDLGameDevelopmentChapter1__TextureManager__) */
