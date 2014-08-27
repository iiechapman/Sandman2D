//
//  Layer.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__Layer__
#define __SDLGameDevelopmentChapter1__Layer__

#include <iostream>
#include <string>
using namespace std;
class Level;

/**
 * \class Layer
 * \brief Layer object Interface
 * \note Meant to be overridden
 * \author Evan Chapman
 * \version 1
 * Contact: iiechapman\@gmail.com
 */
class ILayer{
public:
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual void update(Level* pLevel) = 0;
    
    void setType(string type);
    string getType() const;
    
protected:
    /**< Type of layer , ie object, lighting, tile */
    string m_type;
    
};


#endif /* defined(__SDLGameDevelopmentChapter1__Layer__) */
