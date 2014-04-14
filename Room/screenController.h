//
//  screenController.h
//  Room
//
//  Created by Yue Huang on 2014-04-14.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__screenController__
#define __Room__screenController__

#include <stack>
#include "screen.h"

class ScreenController:public Screen{
    std::stack<Screen *> controller_stack;
    Screen * top;
public:
    ScreenController(Screen * s);
    ~ScreenController();
    void push_controller(Screen * next);
    void pop_controller();
    void pop_controller_to(Screen * s);
    
    void render();
    void update(SDL_Event event);
    
};

#endif /* defined(__Room__screenController__) */
