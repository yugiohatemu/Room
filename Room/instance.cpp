//
//  instance.cpp
//  Room
//
//  Created by Yue Huang on 2014-04-10.
//  Copyright (c) 2014 Yue Huang. All rights reserved.
//

#include "instance.h"

Instance::Instance(){
   
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
    m_texture.load_file("", 0, 0);
    
}

void Instance::clean_all(){
    m_texture.clean_texture();
}

Texture& Instance::texture(){
    return m_texture;
}

BottomInfo& Instance::bottomInfo(){
    return m_bottomInfo;
}