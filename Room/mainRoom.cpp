//
//  mainRoom.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-08.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "mainRoom.h"
#include <OpenGL/OpenGL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <sstream>
#include "instance.h"
#include "item.h"
#include "player.h"
#include "text.h"


MainRoom::MainRoom(){
    pos = Point(240, 320,0);
    next_pos = pos;
    speed_factor = 5;
    one_turn = ONE_TURN_COST;
    
    //TODO: set options to be text
    Item *bed = new Item();
    bed->hitbox = Rect(Point(50,50,0),150,200);
    bed->type = ITEM_BED;
    bed->turn_cost = 7;
    bed->mh_charge = 10;
    bed->ph_charge = 15;
    bed->options[0] = new Text(Point(125, 150,0),"INFO");
    bed->options[1] = new Text(Point(125, 150 + TEXT_HEIGHT,0),"USE");
    bed->info = new Text(Point(0, 400,0),"This is a comfortable bed");
    //yap...
    Item *X = new Item();
    X->hitbox = Rect(Point(500, 50, 0),80 ,80);
    X->type = ITEM_X;
    X->turn_cost = 5;
    X->mh_charge = -10;
    X->ph_charge = -10;
    X->options[0] = new Text(Point(540, 90,0),"INFO");
    X->options[1] = new Text(Point(540, 90 + TEXT_HEIGHT,0),"USE");
    X->info = new Text(Point(0, 400,0),"This is X");
    //
    Item *book = new Item();
    book->hitbox = Rect(Point(50, 350, 0),100 ,60);
    book->type = ITEM_BOOK;
    book->turn_cost = 5;
    book->mh_charge = 5;
    book->ph_charge = -10;
    book->options[0] = new Text(Point(100, 380,0),"INFO");
    book->options[1] = new Text(Point(100, 380 + TEXT_HEIGHT,0),"USE");
    book->info = new Text(Point(0, 400,0),"There are many books in it");
    
    //push everything into a vector...yap
    all_items.push_back(bed);
    all_items.push_back(X);
    all_items.push_back(book);
    
    player = new Player();
    player->hitbox = Rect(Point(),40,120);
    
    turnScreen = new Text(Point(), "Day 1\n");
    //actually we want a underlying background box
    //which is completely different from the box that the screen arrange the text
    timer.count_down = 1500.0f; //or we could just add a click/enter
    timer.restart();
}

MainRoom::~MainRoom(){
    for (unsigned int i = 0; i < all_items.size(); i++) {
        delete all_items[i];
    }
    delete player;
    delete turnScreen;
}

void MainRoom::render(){
    //Event unrelated update
    if (next_pos != pos) {
        float dis =  (next_pos - pos).get_norm();
        if (dis > speed.get_norm()) {
            pos = pos + speed;
        }else{ //if we are close enough
            pos = next_pos;
            speed.x = 0;
            speed.y = 0;
        }
    }
    //deploy the screen shuffeling latter....
    //
    if (!timer.is_timeup()) {
        turnScreen->render();
    }else{
        for (unsigned int i = 0; i < all_items.size(); i++) {
            all_items[i]->render();
        }
        
        glPushMatrix();
        glTranslatef(pos.x, pos.y, 0);
        player->render();
        glPopMatrix();
    }
}

void MainRoom::update(SDL_Event event){
  
    if( event.type == SDL_MOUSEBUTTONDOWN ){
        
        int x, y; SDL_GetMouseState( &x, &y );
        Point new_pos(x,y,0);
        if (next_pos == new_pos) return;

        Vector dir = new_pos - pos;
        float dis = dir.get_norm();
        
        //Get the closeset one as the real next_pos;
        for (unsigned int i = 0; i < all_items.size(); i++) {
            Vector next_dir = all_items[i]->get_closest_dir(pos, dir);
            float next_dis = next_dir.get_norm();
                    
            if (next_dis < dis) {
                dis = next_dis;
                dir = next_dir;
            }
        
        }
        //we can get a vector here, just to make things easy?
        for (unsigned int i = 0; i < all_items.size(); i++) {
            if (all_items[i]->is_item_being_hit(new_pos)) {
                
                if (!all_items[i]->option_hidden) { //note, here should be option->hidden
                    
                    int option_hit = all_items[i]->get_option_being_hit(new_pos);
                    if (option_hit != -1) { //hit actually happens on option
//                        std::cout<<"Hit option "<<option_hit<<std::endl;
                    }
                    
                    if (option_hit == 0) { //0
                        all_items[i]->info_hidden = false;
                    }else if(option_hit == 1){ //use
                        player->physical_health += all_items[i]->ph_charge;
                        player->mental_health += all_items[i]->mh_charge;
                        one_turn -= all_items[i]->turn_cost;
//                        std::cout<<"Ph -  "<<player->physical_health<<" mh - "<<player->mental_health<<" turn left "<<one_turn<<std::endl;
                        if (one_turn <= 0) { //reset
                            one_turn = ONE_TURN_COST;
                            //textScreen.set_text("Stats report")
                            timer.restart(); //we need more ...font
                        }
                        
                    }
                    break;
                }else { //close enough
                    all_items[i]->option_hidden = false;
                }
            }else{
                all_items[i]->option_hidden = true;
                all_items[i]->info_hidden = true;
            }

        }
        
        next_pos = pos + dir;
        dir.normalize();
        speed = dir * speed_factor;
        
    }
    
}
