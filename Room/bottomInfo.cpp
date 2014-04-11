//
//  bottomInfo.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "bottomInfo.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>

BottomInfo::BottomInfo():boarder(Point(0,400,0),640,80), hidden(true){
    
}

void BottomInfo::render(){
    if (hidden) return ;
    glPushMatrix();
    glColor4f(1, 1, 1, 0.5);
    boarder.render();
    
    for (unsigned int i = 0, j = 0; i < info.size(); i++) {
        
    }
    
    glPopMatrix();
}

void BottomInfo::set_info(std::string s){
    info = s;
}