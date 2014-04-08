//
//  rect.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "rect.h"

Rect::Rect(Point left_top, int width, int height){
    //in the order of
    //0 1
    //3 2
    points[0] = left_top;
    points[1] = left_top + Vector(width, 0, 0);
    points[2] = points[1] + Vector(0, height, 0);
    points[3] = left_top + Vector(0, height, 0);
    
}
bool Rect::is_xy_in_rec(int x, int y){
    return (x >= points[0].x && x <= points[1].x && y >= points[0].y && y <= points[3].y);
}

Point Rect::get_closest_intersection(Point pos, Vector dir){
    //check against each interscetion
    int order[] = {0,1,2,3,0 }; //lazy cheat for cycle
    
    for (unsigned int i = 0; i < 4; i++) {
        Vector edge_vec = points[order[i+1]]- points[order[i+1]];
        if (!is_vector_parallel(edge_vec, dir)) {
            
            float t_up = (points[order[i+1]]- pos).cross(edge_vec);
            float u_up = (points[order[i+1]]- pos).cross(dir);
            
            float div_down = ray.cross(edge_vec);
            
            float new_t = t_up / div_down;
            float u =  u_up / div_down;
            
            //within line segment, and less than the previous one, replace it
            if (new_t >= 0 &&  new_t < t && u >= 0 && u <= 1) {
                t = new_t;
            }
        }
    }
    
    
    
    
}