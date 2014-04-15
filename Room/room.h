//
//  Room.h
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__Room__
#define __Room__Room__

#include "algebra.h"
#include <SDL2/SDL_events.h>
#include "rect.h"
#include <vector>
#include "timer.h"

class Player;
class Item;
class Door;
class Room{
    
public:
    Point pos;
    Point next_pos;
    Vector speed;
    std::vector<Item *> all_items;
    std::vector<Door *> doors;
    float speed_factor;
    Player * player;
    Rect hitbox;
    int one_turn;
    
    Room();
    ~Room();
    void render();
    void update(SDL_Event event);
    void reset();
};

#endif /* defined(__Room__Room__) */
