//
//  instance.h
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#ifndef __Room__instance__
#define __Room__instance__

#include "texture.h"
#include "bottomInfo.h"
#include "const.h"
class Instance{
private:
    Instance();  // Private so that it can  not be called
    Instance(Instance const&);             // copy constructor is private
    Instance& operator=(Instance const&);  // assignment operator is private
    Texture m_texture;
    BottomInfo m_bottomInfo;
public:
    static Instance& get();
    void load_all();
    void clean_all();
    Texture& texture();
    BottomInfo& bottomInfo();
};


#endif /* defined(__Room__instance__) */
