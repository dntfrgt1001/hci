//
//  Visualize.cpp
//  HCI
//
//  Created by masakazu nakazawa on 2015/07/08.
//  Copyright (c) 2015年 masakazu. All rights reserved.
//

#include "Visualize.h"

Visualize::Visualize(b2World& world, int pid, int number,
                     int x, int y, int radius)
{
    enc = new Enclosure(world, x, y, radius);
    
    for(int i=0; i<number; i++){
        parts.push_back(new Particle(world, x, y, radius/10));
    }
}

Visualize::~Visualize()
{
    delete enc;
    std::vector<Particle*>::iterator iter;
    for(iter=parts.begin(); iter!=parts.end(); iter++){
        delete *iter;
    }
}

void Visualize::draw(cv::Mat& img)
{
    enc->draw(img);
    
    std::vector<Particle*>::iterator iter;
    for(iter=parts.begin(); iter!=parts.end(); iter++){
        (*iter)->draw(img);
    }
}