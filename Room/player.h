//
//  player.h
//  Room
//
//  Created by Yue Huang on 2014-04-14.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__player__
#define __Room__player__
#include "rect.h"

class Player{
public:
    Player();
    ~Player();
    void render();
    
    Rect hitbox;
    unsigned int type;
    int physical_health;
    int mental_health;
    int progress_of_x; //can only be increased by x
    //more importantly is that we define the stats
};

#endif /* defined(__Room__player__) */
