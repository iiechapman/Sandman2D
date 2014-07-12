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

class Layer{
public:
    
    virtual void render() = 0;
    virtual void update(Level* pLevel) = 0;
    
    void setType(string type) {
        m_type = type;
    }
    string getType() const { return m_type; }
    
protected:
    //virtual ~Layer();
    
    string m_type;
    
};


#endif /* defined(__SDLGameDevelopmentChapter1__Layer__) */
