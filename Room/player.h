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
class Ghost;
class Player{
public:
    Player();
    ~Player();
    void render();
    
    Rect hitbox;
    unsigned int type;
    int physical_health;
    int mental_health;
    int progress_of_x;

    int ph_condition[3];
    int ph_index;
    
    enum Event{
        DO_NOTHING,
        CREATE_ROOM,
        DESTROY_ROOM,
    };
    
    Event get_new_condtion();
    int turn_left;
    Ghost * test_ghost;
};

#endif /* defined(__Room__player__) */
