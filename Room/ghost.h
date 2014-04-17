//
//  ghost.h
//  Room
//
//  Created by Yue Huang on 2014-04-17.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__ghost__
#define __Room__ghost__

#include "algebra.h"
#include "rect.h"
class Ghost{
public:
    Point pos;
    Point next_pos;
    Vector dir;
    float speed_factor;
    Rect hitbox;
    unsigned int type;
    Ghost();
    ~Ghost();
    void render();
    void follow(Point new_pos);
};

#endif /* defined(__Room__ghost__) */
