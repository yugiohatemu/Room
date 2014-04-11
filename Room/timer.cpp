//
//  timer.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "timer.h"
#include <SDL2/SDL_timer.h>

Timer::Timer(){
    count_down = 0;
}

Timer::Timer(float count_down){
    this->count_down = count_down * 1000;
}

Timer::~Timer(){
    
}

bool Timer::is_timeup(){
    time_accum = time_accum +  SDL_GetTicks() - start_tick;
    start_tick = SDL_GetTicks();
    return (time_accum >= count_down);
}

void Timer::start(){
    time_accum = 0;
    start_tick = SDL_GetTicks();
}
