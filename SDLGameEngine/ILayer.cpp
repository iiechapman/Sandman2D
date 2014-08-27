//
//  Layer.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 6/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "ILayer.h"


void ILayer::setType(string type) {
    m_type = type;
}

string ILayer::getType() const {
    return m_type;
}