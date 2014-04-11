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
    Point points[4];
    Rect();
    Rect(Point left_top, int width, int height);
    bool is_pos_in_rec(Point pos);
    void render();
    float width();
    float height();
};

#endif /* defined(__Room__rect__) */
