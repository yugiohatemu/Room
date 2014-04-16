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
    Rect hitbox;
    Room * next_room;
    Door();
    ~Door();
    void render();
};

#endif /* defined(__Room__door__) */
