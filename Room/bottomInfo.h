//
//  bottomInfo.h
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__bottomInfo__
#define __Room__bottomInfo__

#include "rect.h"
#include <string>

class BottomInfo{
    Rect boarder;
    std::string info;
public:
    BottomInfo();
    void render();
    void set_info(std::string s);
    bool hidden;
    //set string
};

#endif /* defined(__Room__bottomInfo__) */
