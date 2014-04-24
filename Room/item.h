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
#include <string>

class Text;

class Item{
   
public:
    bool option_hidden;
    bool info_hidden;
    Rect hitbox;
    Text* options[2];
    Text* info;
    
    unsigned int type;
    int ph_charge; //+ is increase, - is decrease on usage
    int mh_charge; //also each item has a turn cost
    int turn_cost;
    
    Item(bool lazy);
    
    ~Item();
    void render();
    bool is_item_being_hit(Point pos);
    int get_option_being_hit(Point pos);
    std::string item_name;
    bool lazy;
    bool hidden;
//    std::string event;
};

#endif /* defined(__Room__item__) */
