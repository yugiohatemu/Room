//
//  rect.h
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__rect__
#define __Room__rect__

#include "algebra.h"

struct Rect{
    Point top_left;
    float width;
    float height;
    Rect();
    Rect(Point left_top, int width, int height);
    bool is_pos_in_rec(Point pos);
    void render();
    Vector get_closest_dir(Point pos, Vector dir);
};

#endif /* defined(__Room__rect__) */
