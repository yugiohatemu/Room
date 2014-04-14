//
//  rect.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "rect.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
Rect::Rect(){
    
}

Rect::Rect(Point top_left, int width, int height):top_left(top_left), width(width),height(height){
}

void Rect::render(){
    //0 1
    //3 2
    glBegin(GL_QUADS);
    glVertex2f(top_left.x, top_left.y);
    glVertex2f(top_left.x + width, top_left.y);
    glVertex2f(top_left.x + width, top_left.y + height);
    glVertex2f(top_left.x, top_left.y + height);
    glEnd();
}

bool Rect::is_pos_in_rec(Point pos){
    return (pos.x >= top_left.x && pos.x <= top_left.x + width && pos.y >= top_left.y && pos.y <= top_left.y + height);
}
