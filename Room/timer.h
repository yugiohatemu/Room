//
//  timer.h
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__timer__
#define __Room__timer__

class Timer{
    float time_accum;
    int start_tick;
public:
    float count_down;
    Timer();
    Timer(float count_down);
    ~Timer();
    bool is_timeup();
    void restart();
};

#endif /* defined(__Room__timer__) */
