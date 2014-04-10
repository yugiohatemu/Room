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
    Rect hitbox;
    Rect options[2];
public:
    bool hidden;
    
    Item();
    ~Item();
    
    Vector get_closest_dir(Point pos, Vector dir);

    void render();
    bool is_item_being_hit(Point pos);
    int get_option_being_hit(Point pos);
};

#endif /* defined(__Room__item__) */
