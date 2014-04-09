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
/*
Vector Rect::get_closest_dir(Point pos, Vector dir){
    //check against each interscetion
    int order[] = {0,1,2,3,0}; //lazy cheat for cycle
    float t = 1.0f;
    for (unsigned int i = 0; i < 4; i++) { //x * vec.y - y * vec.x
        Vector edge_vec = points[order[i+1]]- points[order[i]];
        float div_down = dir.x * edge_vec.y - dir.y * edge_vec.x;
        
        if (div_down != 0) {
            Vector ray = points[order[i]]- pos;
            float next_t = (ray.x * edge_vec.y - ray.y * edge_vec.x) /div_down;
            float next_u = (ray.x * dir.y - ray.y * dir.x) / div_down;
            
            //within line segment, and less than the previous one, replace it
            if (next_t > 0 &&  next_t < t && next_u >= 0 && next_u <= 1) t = next_t;
        }
    }
    
    return dir * t;
}*/