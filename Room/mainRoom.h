//
//  mainRoom.h
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__mainRoom__
#define __Room__mainRoom__

#include "algebra.h"
#include <SDL2/SDL.h>

class MainRoom{
    Point pos;
    Point next_pos;
    Vector speed;
    float speed_factor;
public:
    MainRoom();
    ~MainRoom();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Room__mainRoom__) */