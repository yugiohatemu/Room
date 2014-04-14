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
#include <SDL2/SDL_events.h>
#include "rect.h"
#include <vector>
#include "timer.h"

class Player;
class Item;
class Text;

class MainRoom{
public:
    Point pos;
    Point next_pos;
    Vector speed;
    std::vector<Item *> all_items;
    float speed_factor;
    Player * player;
    Text * turnScreen;
    int one_turn;
    Timer timer;
    
    MainRoom();
    ~MainRoom();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Room__mainRoom__) */
