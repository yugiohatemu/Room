//
//  door.h
//  Room
//
//  Created by Yue Huang on 2014-04-15.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__door__
#define __Room__door__

#include "rect.h"
class Room;
//could be subclassed of item
class Door{
public:
    enum DOOR_DIR{
        NORTH,
        SOUTH,
        WEST,
        EAST,
        UP, //TODO: later
        DOWN,
    };
    Rect hitbox;
    Room * next_room;
    DOOR_DIR dir;
    Door(DOOR_DIR dir);
    static DOOR_DIR get_rand_dir();
    DOOR_DIR get_opp_dir();
    ~Door();
    void render();
};

#endif /* defined(__Room__door__) */
