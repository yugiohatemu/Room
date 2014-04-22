//
//  instance.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "instance.h"
#include "mainScreen.h"
#include "interScreen.h"
#include "text.h"

Instance::Instance(){
    main_screen = new MainScreen();
    inter_screen = new InterScreen();
    inter_screen->text = new Text(Point(),"I wake up in a room.\nAll I remember is that I need to finish\n it in 30 days. \nOtherwise…");
    screen_shown = INTER_SCREEN;
}

Instance::Instance(Instance const&){
    
}

Instance& Instance::operator=(Instance const&){
    return *this;
}

Instance& Instance::get(){
    static Instance m_Instance;
    return m_Instance;
}

void Instance::load_all(){
    m_texture.load_file("/Users/yuehuang/Desktop/Room/Room/item.png", 256, 256);
    m_texture.load_file("/Users/yuehuang/Desktop/Room/Room/fontTile.png", 512, 512);
}

void Instance::clean_all(){
    m_texture.clean_texture();
    delete main_screen;
    delete inter_screen;
}

Texture& Instance::texture(){
    return m_texture;
}

void Instance::render(){
    if(screen_shown == MAIN_SCREEN){
        main_screen->render();
    }else if(screen_shown == INTER_SCREEN){
        inter_screen->render();
    }else if(screen_shown == MENU_SCREEN){
        
    }
}

void Instance::update(SDL_Event event){
    if(screen_shown == MAIN_SCREEN){
        main_screen->update(event);
    }else if(screen_shown == INTER_SCREEN){
        inter_screen->update(event);
    }else if(screen_shown == MENU_SCREEN){
        //
    }
}