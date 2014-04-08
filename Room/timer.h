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
private:
    float time_accum;
    int start_tick;
    float count_down;
public:
    Timer();
    Timer(float count_down);
    ~Timer();
    bool is_timeup();
    void start();
//    void reset();
//    float get_accum_time();
};

#endif /* defined(__Room__timer__) */
