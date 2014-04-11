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

Rect::Rect(Point left_top, int width, int height){
    //in the order of
    //0 1
    //3 2
    points[0] = left_top;
    points[1] = left_top + Vector(width, 0, 0);
    points[2] = points[1] + Vector(0, height, 0);
    points[3] = left_top + Vector(0, height, 0);
    
}

void Rect::render(){
    glBegin(GL_QUADS);
    for (unsigned int i = 0; i < 4; i++) glVertex2f(points[i].x, points[i].y);
    glEnd();
}

bool Rect::is_pos_in_rec(Point pos){
    return (pos.x >= points[0].x && pos.x <= points[1].x && pos.y >= points[0].y && pos.y <= points[3].y);
}

float Rect::width(){
    return points[1].x - points[0].x;
}
float Rect::height(){
    return points[3].y - points[0].y;
}