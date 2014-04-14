//
//  item.h
//  Room
//
//  Created by Yue Huang on 2014-04-09.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__item__
#define __Room__item__

#include "rect.h"

class Item{
   
public:
    bool hidden;
    Rect hitbox;
    Rect options[2];
    
    unsigned int type;
    int ph_charge; //+ is increase, - is decrease on usage
    int mh_charge; //also each item has a turn cost
    int turn_cost;
    
    Item();
    ~Item();
    void render();
    bool is_item_being_hit(Point pos);
    int get_option_being_hit(Point pos);
    Vector get_closest_dir(Point pos, Vector dir);
};

#endif /* defined(__Room__item__) */
