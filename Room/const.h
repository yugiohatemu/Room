//
//  clip.h
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef Room_const_h
#define Room_const_h
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const float t_TEXT_WIDTH = 0.09375;
const float t_TEXT_HEIGHT = 0.125;

const float TEXT_WIDTH = 24;
const float TEXT_HEIGHT = 40;

const int ONE_TURN_COST = 24;
/*
const float TEXT_CLIP[] = {
    //'A','B','C','D','E','F','G','H','I','J'
    0  ,0,
    0.09375,0,
    0.1875,0,
    0.28125,0,
    0.375,0,
    0.46875,0,
    0.5625,0,
    0.65625,0,
    0.75,0,
    0.84375,0,
    //'K','L','M','N','O','P', 'Q','R','S','T'
    0  ,0.125,
    0.09375,0.125,
    0.1875,0.125,
    0.28125,0.125,
    0.375,0.125,
    0.46875,0.125,
    0.5625,0.125,
    0.65625,0.125,
    0.75,0.125,
    0.84375,0.125,
    //,'U','V','W','X','Y','Z'
    0  ,0.250,
    0.09375,0.250,
    0.1875,0.250,
    0.28125,0.250,
    0.375,0.250,
    0.46875,0.250,
    0.5625,0.250,
    0.65625,0.250,
    0.75,0.250,
    0.84375,0.250,
    //0 - 9
    0  ,0.625,
    0.09375,0.625,
    0.1875,0.625,
    0.28125,0.625,
    0.375,0.625,
    0.46875,0.625,
    0.5625,0.625,
    0.65625,0.625,
    0.75,0.625,
    0.84375,0.625,
    //. , ? ! :
    0  ,0.750,
    0.09375,0.750,
    0.1875,0.750,
    0.28125,0.750,
    0.375,0.750,
};*/

enum ITEM_TYPE{
    ITEM_BED = 0,
    ITEM_X,
    ITEM_FOOD,
    ITEM_BOOK,
    ITEM_CARPET,
    ITEM_PLAYER,
    ITEM_GHOST,
};
//256/8 = 32
const float ITEM_CLIP [] ={
    0,0, 0.250, 0.375, //Bed
    0.250, 0, 0.250, 0.250, //X
    0.250,0.250,0.250,0.125, //Fod
    0.5, 0, 0.375, 0.125, //Book
    0.5,0.125,0.375, 0.250, //carpet
    0, 0.375, 0.125,0.375 ,//player
    0,125,0.5,0.125,0.375 //ghost
};
////Lets finish day 1-10's dialogue first
//const std::string prologue = "I wake up in a room.\nAll I remember is that I need to finish\n it in 30 days. \nOtherwise…";
//const std::string change = "There is something wrong with the room \nbut I can't tell.";
//const std::string stuck = "I get stuck on it. I need clues, or whatever, help.";
//const std::string need_of_friend = "";
#endif
