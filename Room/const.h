//
//  clip.h
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef Room_const_h
#define Room_const_h
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const float TEXT_WIDTH = 0.125;
const float TEXT_HEIGHT = 0.1875;

const int ONE_TURN_COST = 24;

const float TEXT_CLIP[] = {
    //'A','B','C','D','E','F','G','H',
    0  ,0,
    0.125,0,
    0.250,0,
    0.375,0,
    0.500,0,
    0.625,0,
    0.750,0,
    0.875,0,
    //'I','J','K','L','M','N','O','P',
    0  ,0.1875,
    0.125,0.1875,
    0.250,0.1875,
    0.375,0.1875,
    0.500,0.1875,
    0.625,0.1875,
    0.750,0.1875,
    0.875,0.1875,
    //'Q','R','S','T','U','V','W','X',
    0,0.375,
    0.125,0.375,
    0.250,0.375,
    0.375,0.375,
    0.500,0.375,
    0.625,0.375,
    0.750,0.375,
    0.875,0.375,
    //'Y','Z'
    0,0.5625,
    0.125,0.5625,
};

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
    0.5,0.125,0.375, 0.250,
    0, 0.5, 0.125,0.375 ,//player
    0,125,0.5,0.125,0.375 //ghost
};

#endif