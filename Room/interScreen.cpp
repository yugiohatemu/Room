//
//  interScreen.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-14.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "interScreen.h"
#include "text.h"
#include "instance.h"
#include "mainScreen.h" 
#include "mainRoom.h"

InterScreen::InterScreen(){
    
}
InterScreen::~InterScreen(){
    
}

void InterScreen::render(){
    if (text) {
        text->render();
    }
}

void InterScreen::update(SDL_Event event){
    //if we get a click, or space, then update?
    if( event.type == SDL_MOUSEBUTTONDOWN ){
        Instance::get().screen_shown = Instance::MAIN_SCREEN;
        Instance::get().main_screen->main_room->reset();
    }
}