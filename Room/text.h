//
//  text.h
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__text__
#define __Room__text__

#include <string>
#include "rect.h"

class Text{
public:
    Rect hitbox;
    std::string s;

    Text(Point pos, std::string s);
    ~Text();
    void render();
};

#endif /* defined(__Room__text__) */
